#include "barcomms_cfdp.h"
#include "ui_barcomms_cfdp.h"
#include "output.h"
#include "../dependencies/CFDP/CODE/cfdp_code.h"

// Constructor
BARCoMmS_CFDP::BARCoMmS_CFDP(QWidget *parent) : QMainWindow(parent), ui(new Ui::BARCoMmS_CFDP){
    ui->setupUi(this);

    // Hide the input box (used for debugging)
    ui->lineEdit_input->hide();

    // Initalize logFile
    initLogFile("resources/BARCoMmS_CFDP.log");

    // Display BARCoMmS logo
    showLogo("resources/BC_Blue.png");

    // Create all windows
    createWindows();

    // Connect all signals/slots
    establishConnections();

    // Initialize 'non-CFDP' variables
    initVariables();

    // Initialize CFDP structs
    initStructs();

    // Establish a connection within CFDP
    main_cfdp(global_mib.ID);

    // Process CFDP transactions in the background
    startWorkInAThread();
}

// Destructor
BARCoMmS_CFDP::~BARCoMmS_CFDP(){
    delete ui;
}

// Initialize the CFDP transaction handler thread and connect all of its signals and slots
void BARCoMmS_CFDP::startWorkInAThread(){
    workerThread = new Worker();
    connect(workerThread, &Worker::readyToCycleTransactions, this, &BARCoMmS_CFDP::cycleTransactions, Qt::BlockingQueuedConnection);
    connect(workerThread, &Worker::readyToGivePDU, this, &BARCoMmS_CFDP::givePDU, Qt::BlockingQueuedConnection);
    connect(this, &BARCoMmS_CFDP::terminator, workerThread, &Worker::terminate);
    connect(workerThread, &Worker::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

// Handle CFDP transaction and, if periodic status is enabled, display status
void BARCoMmS_CFDP::cycleTransactions(){
    cfdp_cycle_each_transaction();
    updateCyclesSender->displayStatus();
}

// Give the CFDP engine a PDU
void BARCoMmS_CFDP::givePDU(DATA pdu){
    cfdp_give_pdu(pdu);
}

// Display BARCoMmS logo
void BARCoMmS_CFDP::showLogo(QString logo){
    QPixmap logoPixmap(logo);
    ui->label_logo->setPixmap(logoPixmap);
}

// Initialize logFile
void BARCoMmS_CFDP::initLogFile(std::string file){
    this->logFile = file;
}

// Connect all signals and slots
void BARCoMmS_CFDP::establishConnections(){
    // Output Signal/Slot
    connect(outputSender, &Output::output_appendOutput, this, &BARCoMmS_CFDP::output_changeLabel);

    // Sim Signal/Slot
    connect(simSender, &Sim::sim_appendOutput, this, &BARCoMmS_CFDP::sim_changeLabel);

    // Buffer Signal/Slot
    connect(bufferSender, &Buffer::buffer_modifyBuffer, this, &BARCoMmS_CFDP::buffer_changeBuffer);

    // Options Signal/Slot
    connect(optionsSender, &Options::options_modifyOptions, this, &BARCoMmS_CFDP::options_changeOptions);

    // UpdateCycles Signal/Slot
    connect(updateCyclesSender, &UpdateCycles::updateCycles_appendOutput, this, &BARCoMmS_CFDP::updateCycles_changeLabel);
    connect(updateCyclesSender, &UpdateCycles::updateCycles_toggle, this, &BARCoMmS_CFDP::updateCycles_toggleUpdates);

    // Requests Signal/Slot
    connect(requestsSender, &Requests::requests_appendOutput, this, &BARCoMmS_CFDP::requests_changeLabel);

    // ClassMessages Signal/Slot
    connect(classMessagesSender, &ClassMessages::classMessages_appendOutput, this, &BARCoMmS_CFDP::classMessages_changeLabel);

    // Setter Signal/Slot
    connect(setterSender, &Setter::setter_appendOutput, this, &BARCoMmS_CFDP::setter_changeLabel);
}

// Initialize windows used by BARCoMmS_CFDP
void BARCoMmS_CFDP::initWindow(QDialog *window){
    Qt::WindowFlags flags = windowFlags();
    window->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    window->setModal(true);
    window->show();
}

// Create windows used by BARCoMmS_CFDP
void BARCoMmS_CFDP::createWindows(){
    // Sim window
    simSender = new Sim(this);

    // Buffer window
    bufferSender = new Buffer(this);

    // Options window
    optionsSender = new Options(this);

    // UpdateCycles window
    updateCyclesSender = new UpdateCycles(this);

    // Requests window
    requestsSender = new Requests(this);

    // ClassMessages window
    classMessagesSender = new ClassMessages(this);

    // Setter window
    setterSender = new Setter(this);

    // Help window
    helpSender = new Help(this);
}

// Write str (CFDP input) to plainTextEdit_output
void BARCoMmS_CFDP::barcommsprint(std::string str){
    // Print str to plainTextEdit_output
    ui->plainTextEdit_output->insertPlainText(QString::fromStdString(str.append("\n")));

    // Log str if event log is enabled
    if(ui->action_logEvents->isChecked()){
        fout << str;
    }

    // Execute the command in CFDP
    m__execute_user_input(str.c_str());
}

// Write str (CFDP output) to plainTextEdit_output
void BARCoMmS_CFDP::output_changeLabel(char *str){
    // Print str to plainTextEdit_output
    ui->plainTextEdit_output->insertPlainText(str);

    // Log str if event log is enabled
    if(ui->action_logEvents->isChecked()){
        fout << str;
    }

    // Emit signal for BC_Bulletin
    emit toBulletin(str);
}

// Initiate a put request and create the necessary file dialog box for file browsing
void BARCoMmS_CFDP::on_pushButton_put_clicked(){
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Select a File"));

    if(!fileNames.empty()){
        for(unsigned char i = 0; i < fileNames.size(); ++i){
            QFileInfo fileName = fileNames[i];

            std::string put = "put ";
            std::string transferType;
            if(optionsSender->transType == "Class 2"){
                transferType = "-class2 ";
            }
            else{
                transferType = "-class1 ";
            }
            std::string file = fileNames[i].toStdString();
            std::string client = optionsSender->recvID.toStdString();
            std::string destination = optionsSender->destination.toStdString();
            std::string baseName = fileName.baseName().toStdString();
            std::string completeSuffix = fileName.completeSuffix().toStdString();

            barcommsprint(put.append(transferType).append(file).append(" ").append(client).append(" ").append(destination).append("/").append(baseName).append(".").append(completeSuffix));
        }
    }
}

// Prints all CARRS + D requests to plainTextEdit_output
void BARCoMmS_CFDP::requests_changeLabel(std::vector<std::string> requests){
    for(unsigned int i = 0; i < requests.size(); ++i){
        barcommsprint(requests[i]);
    }
}

// Prompt user to exit the BARCoMmS CFDP module
void BARCoMmS_CFDP::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit\nBARCoMmS CFDP?",
                                                              QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        // Terminate CFDP transaction handler thread
        emit terminator();

        // Exit the program
        barcommsprint("exit");
        event->accept();
    }
    else{
        event->ignore();
    }
}

// Calls closeEvent() function
void BARCoMmS_CFDP::on_pushButton_exit_clicked(){
    this->close();
}

// Calls closeEvent() function
void BARCoMmS_CFDP::on_action_exit_triggered(){
    this->close();
}

// Runs the CFDP engine robustness test
void BARCoMmS_CFDP::on_pushButton_robust_clicked(){
    barcommsprint("robust?");
}

// Resets the status of all recorded CFDP stats (eg. total receivers and total frozen transactions)
void BARCoMmS_CFDP::on_pushButton_resetTotals_clicked(){
    barcommsprint("reset_totals");
}

// Toggles echoing in plainTextEdit_output
void BARCoMmS_CFDP::on_pushButton_echo_clicked(){
    barcommsprint("echo");
}

// Displays a list of all current CFDP transactions
void BARCoMmS_CFDP::on_pushButton_list_clicked(){
    barcommsprint("list");
}

// Displays the status of all recorded CFDP stats (eg. total receivers and total frozen transactions)
void BARCoMmS_CFDP::on_pushButton_summary_clicked(){
    barcommsprint("summary");
}

// Displays the status of all current CFDP transactions
void BARCoMmS_CFDP::on_pushButton_transStatus_clicked(){
    barcommsprint("v");
}

// Displays a list of all CFDP commands
void BARCoMmS_CFDP::on_pushButton_help_clicked(){
    initWindow(helpSender);
}

// Displays a list of all CFDP commands
void BARCoMmS_CFDP::on_action_commands_triggered(){
    initWindow(helpSender);
}

// Opens the 'Suspend' window for suspending transactions
void BARCoMmS_CFDP::on_pushButton_suspend_clicked(){
    requestsSender->initializeForm("Suspend", "Suspend the transaction\n(the user can resume it\nlater).", "suspend");
    initWindow(requestsSender);
}

// Opens the 'Abandon' window for abandoning transactions
void BARCoMmS_CFDP::on_pushButton_abandon_clicked(){
    requestsSender->initializeForm("Abandon", "Kill the transaction\nwithout telling the\npartner.", "abandon");
    initWindow(requestsSender);
}

// Opens the 'Cancel' window for canceling transactions
void BARCoMmS_CFDP::on_pushButton_cancel_clicked(){
    requestsSender->initializeForm("Cancel", "Cancel the transaction\n(transaction partner is\nalerted).", "cancel");
    initWindow(requestsSender);
}

// Opens the 'Report' window for reporting transactions
void BARCoMmS_CFDP::on_pushButton_report_clicked(){
    requestsSender->initializeForm("Report", "Report the current\nstatus of a transaction.", "report");
    initWindow(requestsSender);
}

// Opens the 'Resume' window for resuming transactions
void BARCoMmS_CFDP::on_pushButton_resume_clicked(){
    requestsSender->initializeForm("Resume", "Resume the transaction\n(the user can resume\nsuspended transactions).", "resume");
    initWindow(requestsSender);
}

// Opens the 'Detailed Status' window for displaying the detailed status of transactions
void BARCoMmS_CFDP::on_pushButton_detailedStatus_clicked(){
    requestsSender->initializeForm("Detailed Status", "Provide details\npertaining to the\ntransaction's status.", "detailed_status");
    initWindow(requestsSender);
}

// Opens the 'Message Classes' window for displaying classes of messages
void BARCoMmS_CFDP::on_pushButton_classMessages_clicked(){
    classMessagesSender->classMessages_changeLoadVals();
    initWindow(classMessagesSender);
}

// Opens the 'Link Simulator' window for fault injection testing
void BARCoMmS_CFDP::on_pushButton_sim_clicked(){
    simSender->sim_changeLoadVals();
    initWindow(simSender);
}

// Opens the 'MIB' window for setting MIB parameters
void BARCoMmS_CFDP::on_pushButton_setter_clicked(){
    setterSender->setter_changeLoadVals();
    initWindow(setterSender);
}

// Opens the 'Options' window for setting specific receiver information (eg. receiver's entity ID)
void BARCoMmS_CFDP::on_action_options_triggered(){
    optionsSender->options_changeLoadVals();
    initWindow(optionsSender);
}

// Opens the 'Buffer Size' window for changing the buffer size on plainTextEdit_output
void BARCoMmS_CFDP::on_action_setBufferSize_triggered(){
    bufferSender->buffer_changeLoadVals();
    initWindow(bufferSender);
}

// Compares the old values of 'Options' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::options_changeOptions(QString transType, QString recvID, QString destination){
    if(transType != optionsSender->transType){
        optionsSender->transType = transType;
        ui->plainTextEdit_output->insertPlainText("Transfer type set to \"" + optionsSender->transType + "\"\n");
    }
    if(recvID != optionsSender->recvID){
        optionsSender->recvID = recvID;
        ui->plainTextEdit_output->insertPlainText("Client set to " + optionsSender->recvID + '\n');
    }
    if(destination != optionsSender->destination){
        optionsSender->destination = destination;
        ui->plainTextEdit_output->insertPlainText("Destination set to \"" + optionsSender->destination + "\"\n");
    }
}

// Compares the old values of 'Buffer Size' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::buffer_changeBuffer(unsigned int bufferSize){
    if(bufferSize != bufferSender->bufferSize){
        bufferSender->bufferSize = bufferSize;
        if(bufferSender->bufferSize == 0){
            ui->plainTextEdit_output->setMaximumBlockCount(bufferSender->bufferSize);
        }
        else{
            ui->plainTextEdit_output->setMaximumBlockCount(bufferSender->bufferSize + 1);
        }
        ui->plainTextEdit_output->insertPlainText("Buffer size set to " + QString::number(bufferSender->bufferSize) + '\n');
    }
}

// Prints input to plainTextEdit_output to be handled by CFDP
void BARCoMmS_CFDP::on_lineEdit_input_returnPressed(){
    barcommsprint(ui->lineEdit_input->text().toStdString());
    ui->lineEdit_input->clear();
}

// Clears plainTextEdit_output
void BARCoMmS_CFDP::on_action_clearScreen_triggered(){
    ui->plainTextEdit_output->clear();
}

// Opens/closes the log file for writing
void BARCoMmS_CFDP::on_action_logEvents_toggled(bool checked){
    if(checked){
        ui->plainTextEdit_output->insertPlainText("Event log enabled\n");

        //Open logFile for writing
        fout.open(logFile, std::fstream::app | std::fstream::out);

        if(!fout.is_open()){
            ui->plainTextEdit_output->insertPlainText("Failed to open file \"" + QString::fromStdString(logFile) + "\"\n");
            ui->action_logEvents->setChecked(0);
            return;
        }
    }
    else{
        ui->plainTextEdit_output->insertPlainText("Event log disabled\n");

        //Close logFile if it is open
        if(fout.is_open()){
            fout.close();
        }
    }
}

// Compares the old values of 'Link Simulator' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::sim_changeLabel(LinkSim linkSim){
    if(linkSim.rate != global_linkSim.rate){
        global_linkSim.rate = linkSim.rate;
        std::string str = "sim success_rate=";
        barcommsprint(str.append(std::to_string(global_linkSim.rate)));
    }
    if(linkSim.delay != global_linkSim.delay){
        global_linkSim.delay = linkSim.delay;
        std::string str = "sim delay_between_pdus=";
        barcommsprint(str.append(std::to_string(global_linkSim.delay)));
    }
    if(strcmp(linkSim.mode, global_linkSim.mode)){
        strcpy(global_linkSim.mode, linkSim.mode);
        barcommsprint(global_linkSim.mode);
    }
    if(strcmp(linkSim.corruption, global_linkSim.corruption)){
        strcpy(global_linkSim.corruption, linkSim.corruption);
        barcommsprint(global_linkSim.corruption);
    }
}

// Compares the old values of 'Message Classes' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::classMessages_changeLabel(MessageClasses messageClasses){
    if(messageClasses.all != global_messageClasses.all){
        global_messageClasses.all = messageClasses.all;

        if(!global_messageClasses.indications && !global_messageClasses.debugMemoryUse && !global_messageClasses.debugNAK &&
                !global_messageClasses.debugPDU && !global_messageClasses.PDUFiledata && !global_messageClasses.PDUNonFiledata &&
                !global_messageClasses.PDURetransmittedFD && !global_messageClasses.stateAll && !global_messageClasses.stateChange){
            global_messageClasses.indications = messageClasses.indications;
            global_messageClasses.debugMemoryUse = messageClasses.debugMemoryUse;
            global_messageClasses.debugNAK = messageClasses.debugNAK;
            global_messageClasses.debugPDU = messageClasses.debugPDU;
            global_messageClasses.PDUFiledata = messageClasses.PDUFiledata;
            global_messageClasses.PDUNonFiledata = messageClasses.PDUNonFiledata;
            global_messageClasses.PDURetransmittedFD = messageClasses.PDURetransmittedFD;
            global_messageClasses.stateAll = messageClasses.stateAll;
            global_messageClasses.stateChange = messageClasses.stateChange;
            barcommsprint("class+ all");
            return;
        }
        else if(!messageClasses.indications && !messageClasses.debugMemoryUse && !messageClasses.debugNAK &&
                !messageClasses.debugPDU && !messageClasses.PDUFiledata && !messageClasses.PDUNonFiledata &&
                !messageClasses.PDURetransmittedFD && !messageClasses.stateAll && !messageClasses.stateChange){
            global_messageClasses.indications = messageClasses.indications;
            global_messageClasses.debugMemoryUse = messageClasses.debugMemoryUse;
            global_messageClasses.debugNAK = messageClasses.debugNAK;
            global_messageClasses.debugPDU = messageClasses.debugPDU;
            global_messageClasses.PDUFiledata = messageClasses.PDUFiledata;
            global_messageClasses.PDUNonFiledata = messageClasses.PDUNonFiledata;
            global_messageClasses.PDURetransmittedFD = messageClasses.PDURetransmittedFD;
            global_messageClasses.stateAll = messageClasses.stateAll;
            global_messageClasses.stateChange = messageClasses.stateChange;
            barcommsprint("class- all");
            return;
        }
    }

    if(messageClasses.indications != global_messageClasses.indications){
        global_messageClasses.indications = messageClasses.indications;
        global_messageClasses.indications ? barcommsprint("class+ indications") : barcommsprint("class- indications");
    }

    if(messageClasses.debugMemoryUse != global_messageClasses.debugMemoryUse){
        global_messageClasses.debugMemoryUse = messageClasses.debugMemoryUse;
        global_messageClasses.debugMemoryUse ? barcommsprint("class+ debug_memory_use") : barcommsprint("class- debug_memory_use");
    }

    if(messageClasses.debugNAK != global_messageClasses.debugNAK){
        global_messageClasses.debugNAK = messageClasses.debugNAK;
        global_messageClasses.debugNAK ? barcommsprint("class+ debug_nak") : barcommsprint("class- debug_nak");
    }

    if(messageClasses.debugPDU != global_messageClasses.debugPDU){
        global_messageClasses.debugPDU = messageClasses.debugPDU;
        global_messageClasses.debugPDU ? barcommsprint("class+ debug_pdu") : barcommsprint("class- debug_pdu");
    }

    if(messageClasses.PDUFiledata != global_messageClasses.PDUFiledata){
        global_messageClasses.PDUFiledata = messageClasses.PDUFiledata;
        global_messageClasses.PDUFiledata ? barcommsprint("class+ pdu_filedata") : barcommsprint("class- pdu_filedata");
    }

    if(messageClasses.PDUNonFiledata != global_messageClasses.PDUNonFiledata){
        global_messageClasses.PDUNonFiledata = messageClasses.PDUNonFiledata;
        global_messageClasses.PDUNonFiledata ? barcommsprint("class+ pdu_non_filedata") : barcommsprint("class- pdu_non_filedata");
    }

    if(messageClasses.PDURetransmittedFD != global_messageClasses.PDURetransmittedFD){
        global_messageClasses.PDURetransmittedFD = messageClasses.PDURetransmittedFD;
        global_messageClasses.PDURetransmittedFD ? barcommsprint("class+ pdu_retransmitted_fd") : barcommsprint("class- pdu_retransmitted_fd");
    }

    if(messageClasses.stateAll != global_messageClasses.stateAll){
        global_messageClasses.stateAll = messageClasses.stateAll;
        global_messageClasses.stateAll ? barcommsprint("class+ state_all") : barcommsprint("class- state_all");
    }

    if(messageClasses.stateChange != global_messageClasses.stateChange){
        global_messageClasses.stateChange = messageClasses.stateChange;
        global_messageClasses.stateChange ? barcommsprint("class+ state_change") : barcommsprint("class- state_change");
    }
}

// Compares the old values of 'MIB' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::setter_changeLabel(MIB mib){
    std::string str;

    if(strcmp(mib.EOFSent, global_mib.EOFSent)){
        strcpy(global_mib.EOFSent, mib.EOFSent);

        // Convert to lower case for printing
        std::string temp = global_mib.EOFSent;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_eof_sent ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.EOFRecv, global_mib.EOFRecv)){
        strcpy(global_mib.EOFRecv, mib.EOFRecv);

        // Convert to lower case for printing
        std::string temp = global_mib.EOFRecv;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_eof_recv ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.fileSent, global_mib.fileSent)){
        strcpy(global_mib.fileSent, mib.fileSent);

        // Convert to lower case for printing
        std::string temp = global_mib.fileSent;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_file_segment_sent ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.fileRecv, global_mib.fileRecv)){
        strcpy(global_mib.fileRecv, mib.fileRecv);

        // Convert to lower case for printing
        std::string temp = global_mib.fileRecv;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_file_segment_recv ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.resumed, global_mib.resumed)){
        strcpy(global_mib.resumed, mib.resumed);

        // Convert to lower case for printing
        std::string temp = global_mib.resumed;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_resumed ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.suspended, global_mib.suspended)){
        strcpy(global_mib.suspended, mib.suspended);

        // Convert to lower case for printing
        std::string temp = global_mib.suspended;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_suspended ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.transFin, global_mib.transFin)){
        strcpy(global_mib.transFin, mib.transFin);

        // Convert to lower case for printing
        std::string temp = global_mib.transFin;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set issue_transaction_finished ";
        barcommsprint(str.append(temp));
    }

    if(strcmp(mib.save, global_mib.save)){
        strcpy(global_mib.save, mib.save);

        // Convert to lower case for printing
        std::string temp = global_mib.save;
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        str = "set save_incomplete_files ";
        barcommsprint(str.append(temp));
    }

    if(mib.ACKLimit != global_mib.ACKLimit){
        global_mib.ACKLimit = mib.ACKLimit;
        str = "set ack_limit ";
        barcommsprint(str.append(std::to_string(global_mib.ACKLimit)));
    }

    if(mib.ACKTimeout != global_mib.ACKTimeout){
        global_mib.ACKTimeout = mib.ACKTimeout;
        str = "set ack_timeout ";
        barcommsprint(str.append(std::to_string(global_mib.ACKTimeout)));
    }

    if(mib.NAKLimit != global_mib.NAKLimit){
        global_mib.NAKLimit = mib.NAKLimit;
        str = "set nak_limit ";
        barcommsprint(str.append(std::to_string(global_mib.NAKLimit)));
    }

    if(mib.NAKTimeout != global_mib.NAKTimeout){
        global_mib.NAKTimeout = mib.NAKTimeout;
        str = "set nak_timeout ";
        barcommsprint(str.append(std::to_string(global_mib.NAKTimeout)));
    }

    if(mib.inactivity != global_mib.inactivity){
        global_mib.inactivity = mib.inactivity;
        str = "set inactivity_timeout ";
        barcommsprint(str.append(std::to_string(global_mib.inactivity)));
    }

    if(mib.chunkSize != global_mib.chunkSize){
        global_mib.chunkSize = mib.chunkSize;
        str = "set outgoing_file_chunk_size ";
        barcommsprint(str.append(std::to_string(global_mib.chunkSize)));
    }

    if(strcmp(mib.ID, global_mib.ID)){
        strcpy(global_mib.ID, mib.ID);

        str = "set my_id ";
        barcommsprint(str.append(global_mib.ID));
    }
}

// Freezes/thaws the CFDP engine
void BARCoMmS_CFDP::on_pushButton_freeze_toggled(bool depressed){
    if(depressed){
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Freeze", "Will \'freeze\' the engine.", QMessageBox::Close);
        if(reply == QMessageBox::Close){
            barcommsprint("freeze");
        }
    }
    else{
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Thaw", "Will \'thaw\' the engine.", QMessageBox::Close);
        if(reply == QMessageBox::Close){
            barcommsprint("thaw");
        }
    }
}

// Disables/enables CFDP engine messages
void BARCoMmS_CFDP::on_pushButton_disableEngineMessages_toggled(bool depressed){
    if(depressed){
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Disable Engine Messages", "Disabling engine messages.", QMessageBox::Close);
        if(reply == QMessageBox::Close){
            barcommsprint("disable_engine_messages");
        }
    }
    else{
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Enable Engine Messages", "Enabling engine messages.", QMessageBox::Close);
        if(reply == QMessageBox::Close){
            barcommsprint("enable_engine_messages");
        }
    }
}

// Disables/enables periodic status updates
void BARCoMmS_CFDP::on_pushButton_periodicStatus_toggled(bool depressed){
    if(depressed){
        updateCyclesSender->updateCycles_changeLoadVals();
        initWindow(updateCyclesSender);
    }
    else{
        if(updateCyclesSender->periodicStatus){
            updateCyclesSender->periodicStatus ^= 1;
            barcommsprint("n");
        }
    }
}

// Compares the old values of 'Periodic Status Updates' variables to the new values and updates if they are different, then executes the changed commands
void BARCoMmS_CFDP::updateCycles_changeLabel(unsigned int updateRate){
    if(updateRate != updateCyclesSender->updateRate){
        updateCyclesSender->updateRate = updateRate;
        std::string str = "update ";
        barcommsprint(str.append(std::to_string(updateCyclesSender->updateRate)));
    }

    barcommsprint("n");
}

// Toggles the 'Periodic Status Updates' button
void BARCoMmS_CFDP::updateCycles_toggleUpdates(){
    ui->pushButton_periodicStatus->toggle();
}

// Checks if auto-scroll is enabled and, if so, scrolls as new text is added to plainTextEdit_output
void BARCoMmS_CFDP::on_plainTextEdit_output_textChanged(){
    if(ui->action_autoScroll->isChecked()){
        ui->plainTextEdit_output->ensureCursorVisible();
    }
}

// Initialize all 'non-CFDP' variables
void BARCoMmS_CFDP::initVariables(){
    char line[255];
    char result[255];

    FILE *fp = fopen("resources/BARCoMmS_CFDP.init", "r");

    if(fp != NULL){
        while(fgets(line, sizeof(line), fp)){
            // For Options parameters
            if(strstr(line, "Transfer Type:")){
                toLower(extractVal(line, result));

                if(!strcmp(result, "class 1")){
                    optionsSender->transType = "Class 1";
                }
                else if(!strcmp(result, "class 2")){
                    optionsSender->transType = "Class 2";
                }
                else{
                    // Default transType to 'Class 1'
                    optionsSender->transType = "Class 1";
                }
            }
            if(strstr(line, "Receiver's Entity ID:")){
                optionsSender->recvID = extractVal(line, result);
            }
            if(strstr(line, "File Destination:")){
                optionsSender->destination = extractVal(line, result);
            }

            // For Misc. parameters
            if(strstr(line, "Cycles Between Updates:")){
                updateCyclesSender->updateRate = atoi(extractVal(line, result));
            }
            if(strstr(line, "Buffer Size:")){
                bufferSender->bufferSize = atoi(extractVal(line, result));
            }
            if(strstr(line, "Log Events?")){
                if(toBoolean(extractVal(line, result))){
                    ui->action_logEvents->setChecked(1);
                }
                else if(!toBoolean(extractVal(line, result))){
                    ui->action_logEvents->setChecked(0);
                }
            }
            if(strstr(line, "Auto Scroll?")){
                if(toBoolean(extractVal(line, result))){
                    ui->action_autoScroll->setChecked(1);
                }
                else if(!toBoolean(extractVal(line, result))){
                    ui->action_autoScroll->setChecked(0);
                }
            }
        }

        memset(line, 0, sizeof(char));
        memset(result, 0, sizeof(char));

        fclose(fp);
    }
}
