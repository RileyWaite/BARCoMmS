#include "classmessages.h"
#include "ui_classmessages.h"

// Constructor
ClassMessages::ClassMessages(QWidget *parent) : QDialog(parent), ui(new Ui::ClassMessages){
    ui->setupUi(this);

    ui->checkBox_all->setToolTip("If enabled, all of the message-classes will be enabled");
    ui->checkBox_indications->setToolTip("If enabled, a message is output each time an indication occurs");
    ui->checkBox_debugMemoryUse->setToolTip("If enabled, this message class provides information needed to\ndebug problems within the engine (related to memory use for\nstoring 'Nak' PDUs)");
    ui->checkBox_debugNAK->setToolTip("If enabled, this message class provides information needed to\ndebug problems within the engine (related to maintenance of\nlists of missing data)");
    ui->checkBox_debugPDU->setToolTip("If enabled, the raw contents of incoming and outgoing PDUs\nare displayed");
    ui->checkBox_PDUFiledata->setToolTip("If enabled, a message is output each time a Filedata PDU is\nreceived");
    ui->checkBox_PDUNonFiledata->setToolTip("If enabled, a message is output each time a File Directive PDU\nis sent or received");
    ui->checkBox_PDURetransmittedFD->setToolTip("If enabled, a message is output each time a Filedata PDU is\nretransmitted");
    ui->checkBox_stateAll->setToolTip("If enabled, a message is output every time a state machine\nruns (lots of messages!)");
    ui->checkBox_stateChange->setToolTip("If enabled, a message is output each time their is a state\nchange within a state machine");
}

// Destructor
ClassMessages::~ClassMessages(){
    delete ui;
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP what the new 'Message Classes' parameters' values are
void ClassMessages::on_buttonBox_accepted(){
    MessageClasses messageClasses;

    messageClasses.all = 0;
    messageClasses.indications = 0;
    messageClasses.debugMemoryUse = 0;
    messageClasses.debugNAK = 0;
    messageClasses.debugPDU = 0;
    messageClasses.PDUFiledata = 0;
    messageClasses.PDUNonFiledata = 0;
    messageClasses.PDURetransmittedFD = 0;
    messageClasses.stateAll = 0;
    messageClasses.stateChange = 0;

    if(ui->checkBox_all->isChecked()){
        messageClasses.all = 1;
        messageClasses.indications = 1;
        messageClasses.debugMemoryUse = 1;
        messageClasses.debugNAK = 1;
        messageClasses.debugPDU = 1;
        messageClasses.PDUFiledata = 1;
        messageClasses.PDUNonFiledata = 1;
        messageClasses.PDURetransmittedFD = 1;
        messageClasses.stateAll = 1;
        messageClasses.stateChange = 1;
    }
    else{
        (ui->checkBox_indications->isChecked()) ? (messageClasses.indications = 1) : (messageClasses.indications = 0);

        (ui->checkBox_debugMemoryUse->isChecked()) ? (messageClasses.debugMemoryUse = 1) : (messageClasses.debugMemoryUse = 0);

        (ui->checkBox_debugNAK->isChecked()) ? (messageClasses.debugNAK = 1) : (messageClasses.debugNAK = 0);

        (ui->checkBox_debugPDU->isChecked()) ? (messageClasses.debugPDU = 1) : (messageClasses.debugPDU = 0);

        (ui->checkBox_PDUFiledata->isChecked()) ? (messageClasses.PDUFiledata = 1) : (messageClasses.PDUFiledata = 0);

        (ui->checkBox_PDUNonFiledata->isChecked()) ? (messageClasses.PDUNonFiledata = 1) : (messageClasses.PDUNonFiledata = 0);

        (ui->checkBox_PDURetransmittedFD->isChecked()) ? (messageClasses.PDURetransmittedFD = 1) : (messageClasses.PDURetransmittedFD = 0);

        (ui->checkBox_stateAll->isChecked()) ? (messageClasses.stateAll = 1) : (messageClasses.stateAll = 0);

        (ui->checkBox_stateChange->isChecked()) ? (messageClasses.stateChange = 1) : (messageClasses.stateChange = 0);
    }

    emit classMessages_appendOutput(messageClasses);
}

// Checks all check boxes if 'All' is manually checked. Unchekcs all check boxes if 'All' is manually unchecked
void ClassMessages::on_checkBox_all_toggled(bool checked){
    if(checked){
        ui->checkBox_indications->setChecked(1);
        ui->checkBox_debugMemoryUse->setChecked(1);
        ui->checkBox_debugNAK->setChecked(1);
        ui->checkBox_debugPDU->setChecked(1);
        ui->checkBox_PDUFiledata->setChecked(1);
        ui->checkBox_PDUNonFiledata->setChecked(1);
        ui->checkBox_PDURetransmittedFD->setChecked(1);
        ui->checkBox_stateAll->setChecked(1);
        ui->checkBox_stateChange->setChecked(1);
    }
    else{
        ui->checkBox_indications->setChecked(0);
        ui->checkBox_debugMemoryUse->setChecked(0);
        ui->checkBox_debugNAK->setChecked(0);
        ui->checkBox_debugPDU->setChecked(0);
        ui->checkBox_PDUFiledata->setChecked(0);
        ui->checkBox_PDUNonFiledata->setChecked(0);
        ui->checkBox_PDURetransmittedFD->setChecked(0);
        ui->checkBox_stateAll->setChecked(0);
        ui->checkBox_stateChange->setChecked(0);
    }
}

// Checks if all check boxes are checked. If so, it checks the 'All' checkbox. If not, it unchecks the 'All' checkbox
void ClassMessages::checker(){
    if(!(ui->checkBox_indications->isChecked()) || !(ui->checkBox_debugMemoryUse->isChecked()) ||
            !(ui->checkBox_debugNAK->isChecked()) || !(ui->checkBox_debugPDU->isChecked()) ||
            !(ui->checkBox_PDUFiledata->isChecked()) || !(ui->checkBox_PDUNonFiledata->isChecked()) ||
            !(ui->checkBox_PDURetransmittedFD->isChecked()) || !(ui->checkBox_stateAll->isChecked()) ||
            !(ui->checkBox_stateChange->isChecked())){
        bool indications = ui->checkBox_indications->isChecked();
        bool debugMemoryUse = ui->checkBox_debugMemoryUse->isChecked();
        bool debugNAK = ui->checkBox_debugNAK->isChecked();
        bool debugPdu = ui->checkBox_debugPDU->isChecked();
        bool pduFiledata = ui->checkBox_PDUFiledata->isChecked();
        bool pduNonFiledata = ui->checkBox_PDUNonFiledata->isChecked();
        bool pduRetransmittedFd = ui->checkBox_PDURetransmittedFD->isChecked();
        bool stateAll = ui->checkBox_stateAll->isChecked();
        bool stateChange = ui->checkBox_stateChange->isChecked();

        ui->checkBox_all->setChecked(0);
        ui->checkBox_indications->setChecked(indications);
        ui->checkBox_debugMemoryUse->setChecked(debugMemoryUse);
        ui->checkBox_debugNAK->setChecked(debugNAK);
        ui->checkBox_debugPDU->setChecked(debugPdu);
        ui->checkBox_PDUFiledata->setChecked(pduFiledata);
        ui->checkBox_PDUNonFiledata->setChecked(pduNonFiledata);
        ui->checkBox_PDURetransmittedFD->setChecked(pduRetransmittedFd);
        ui->checkBox_stateAll->setChecked(stateAll);
        ui->checkBox_stateChange->setChecked(stateChange);
    }
    else{
        ui->checkBox_all->setChecked(1);
    }
}

void ClassMessages::on_checkBox_indications_toggled(){
    checker();
}

void ClassMessages::on_checkBox_debugMemoryUse_toggled(){
    checker();
}

void ClassMessages::on_checkBox_debugNAK_toggled(){
    checker();
}

void ClassMessages::on_checkBox_debugPDU_toggled(){
    checker();
}

void ClassMessages::on_checkBox_PDUFiledata_toggled(){
    checker();
}

void ClassMessages::on_checkBox_PDUNonFiledata_toggled(){
    checker();
}

void ClassMessages::on_checkBox_PDURetransmittedFD_toggled(){
    checker();
}

void ClassMessages::on_checkBox_stateAll_toggled(){
    checker();
}

void ClassMessages::on_checkBox_stateChange_toggled(){
    checker();
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void ClassMessages::classMessages_changeLoadVals(){
    ui->checkBox_all->setChecked(global_messageClasses.all);
    ui->checkBox_indications->setChecked(global_messageClasses.indications);
    ui->checkBox_debugMemoryUse->setChecked(global_messageClasses.debugMemoryUse);
    ui->checkBox_debugNAK->setChecked(global_messageClasses.debugNAK);
    ui->checkBox_debugPDU->setChecked(global_messageClasses.debugPDU);
    ui->checkBox_PDUFiledata->setChecked(global_messageClasses.PDUFiledata);
    ui->checkBox_PDUNonFiledata->setChecked(global_messageClasses.PDUNonFiledata);
    ui->checkBox_PDURetransmittedFD->setChecked(global_messageClasses.PDURetransmittedFD);
    ui->checkBox_stateAll->setChecked(global_messageClasses.stateAll);
    ui->checkBox_stateChange->setChecked(global_messageClasses.stateChange);
}
