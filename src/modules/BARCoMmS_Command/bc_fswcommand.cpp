#include "bc_fswcommand.h"
#include "ui_bc_fswcommand.h"


BC_FSWCommand::BC_FSWCommand(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BC_FSWCommand)
{
    ui->setupUi(this);

    //Reads last command ID used and stores value in numberOfCommands so sequential IDs can begin here
    //If for some reason the file is not opened, the application will start command IDs at zero
    QFile cmdSeqIdFile("resources/cmdSeqId.log");
    if(!cmdSeqIdFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open the file containing the last command ID (to read)";
        numberOfCommands = 0;
    }
    else
    {
        QTextStream in(&cmdSeqIdFile);
        numberOfCommands = in.readAll().toInt();
        cmdSeqIdFile.close();
    }

    //QLCDNumber to display the received signal strength from the health and status packet
    ui->RSSI->setDigitCount(3);
    ui->RSSI->display(0);

    //Create telemetry activity light
    telAct = new QGraphicsScene;
    telActLight = telAct->addEllipse(0,0,20,20,QPen(QColor(0,0,0)),QBrush(QColor(200,50,50)));
    telActLight->setToolTip("Lights up when receiving telemetry.\nGreen: Active\nRed: Inactive");
    ui->gs_RSSI->setScene(telAct);    
    telActTimer->setSingleShot(true);
    connect(telActTimer, SIGNAL(timeout()), this, SLOT(telActOff()));

    //Add BARCoMmS logo
    ui->logo->setAlignment(Qt::AlignHCenter);
    QPixmap pixmap("resources/BC_Red.png");
    ui->logo->setPixmap(pixmap);

    //Set text for push buttons
    ui->fsw_command->setText("FSW Command");
    ui->comm_schedule->setText("Comm Schedule");
    ui->telem_query->setText("Telem Query");
    ui->gnc->setText("GNC");
    ui->decom_commit->setText("Decom Commit");
    ui->decom_enable->setText("Decom Enable");
    ui->prop_schedule->setText("Prop schedule");
    ui->safe_mode->setText("Safe Mode");
    ui->oper_mode->setText("Oper Mode");
    ui->abort_comm_pass->setText("Abort Comm Pass");
    ui->camera_capture_img->setText("Camera Capture Image");
    ui->download_image->setText("Download Image");
    ui->set_dev_avail->setText("Set Device Available");
    ui->set_dev_power->setText("Set Device Power");
    ui->reset_dev->setText("Reset Device");
    ui->fsw_restart->setText("FSW Restart");
    ui->fsw_reboot->setText("FSW Reboot");
    ui->transmit_data_rate->setText("Transmit Data Rate");
    ui->event_retrans->setText("Event Retransmit");

    //Connect push buttons to send respective command
    connect(ui->fsw_command, SIGNAL(clicked()), this, SLOT(fsw_command()));
    connect(ui->but_DL, SIGNAL(clicked()), this, SLOT(downlink_buffer()));
    connect(ui->but_Ping, SIGNAL(clicked()), this, SLOT(ping()));
    connect(ui->comm_schedule, SIGNAL(clicked()), this, SLOT(comm_schedule()));
    connect(ui->telem_query, SIGNAL(clicked()), this, SLOT(telem_query()));
    connect(ui->gnc, SIGNAL(clicked()), this, SLOT(gnc()));
    connect(ui->decom_commit, SIGNAL(clicked()), this, SLOT(decom_commit()));
    connect(ui->decom_enable, SIGNAL(clicked()), this, SLOT(decom_enable()));
    connect(ui->prop_schedule, SIGNAL(clicked()), this, SLOT(prop_schedule()));
    connect(ui->safe_mode, SIGNAL(clicked()), this, SLOT(safe_mode()));
    connect(ui->oper_mode, SIGNAL(clicked()), this, SLOT(oper_mode()));
    connect(ui->abort_comm_pass, SIGNAL(clicked()), this, SLOT(abort_comm_pass()));
    connect(ui->camera_capture_img, SIGNAL(clicked()), this, SLOT(camera_capture_img()));
    connect(ui->download_image, SIGNAL(clicked()), this, SLOT(camera_download_imgs()));
    connect(ui->set_dev_avail, SIGNAL(clicked()), this, SLOT(set_dev_avail()));
    connect(ui->set_dev_power, SIGNAL(clicked()), this, SLOT(set_dev_power()));
    connect(ui->reset_dev, SIGNAL(clicked()), this, SLOT(reset_dev()));
    connect(ui->fsw_restart, SIGNAL(clicked()), this, SLOT(fsw_restart()));
    connect(ui->fsw_reboot, SIGNAL(clicked()), this, SLOT(fsw_reboot()));
    connect(ui->transmit_data_rate, SIGNAL(clicked()), this, SLOT(transmit_data_rate()));
    connect(ui->event_retrans, SIGNAL(clicked()), this, SLOT(event_retrans()));

    //Opens dialog window for user to fill in CAMERA_CAPTURE_IMG command parameters
    //Will eventually need for other commands w/ parameters
    cameraCaptureImgWindow = new Camera_Capture_Img_Window(this);
    connect(cameraCaptureImgWindow, SIGNAL(fields(int, int)), this, SLOT(send_camera_capture_img(int, int)));

    //Opens dialog window for user to fill in CAMERA_DOWNLOAD_IMGS command parameters
    cameraDownloadImgsWindow = new Camera_Download_Imgs_Window(this);
    connect(cameraDownloadImgsWindow, SIGNAL(fields(int)), this, SLOT(send_camera_download_imgs(int)));

    //Set endpoints for UDP connection
    src = EndPoint("138.115.163.120", 1113);
    dest = EndPoint("138.115.163.170", 1113);

    //Create connection between endpoints
    connection.create(src);
    connection.setDestEndPoint(dest);
}

BC_FSWCommand::~BC_FSWCommand()
{
    delete ui;
}

//Displays informative window (Exit)
void BC_FSWCommand::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit\nBARCoMmS Command?",
                                                                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        //Erase number in file and write current numberOfCommands
        QFile cmdSeqIdFile("resources/cmdSeqId.log");
        if(!cmdSeqIdFile.open(QIODevice::WriteOnly))
        {
            qDebug() << "Could not open the file containing the last command ID (to write)";
        }
        else
        {
            QTextStream out(&cmdSeqIdFile);
            out << numberOfCommands;
            cmdSeqIdFile.close();
        }

        //Signal to BC_PacketListenerThread to tell it that a user has died
        emit dying();
        event->accept();
    }
    else event->ignore();
}

//Create and send FSW_COMMAND
void BC_FSWCommand::fsw_command()
{
    //Register that new command is being sent
    numberOfCommands++;

    //Clear the byte buffer
    buf.clear();

    //Instantiate specific command's class, which contains CCSDS header and specific command parameters
    isat_trek::FSW_Control_Command command;

    //Set command's unique ID equal to number of commands sent
    command.LDP_ENDPOINT = numberOfCommands;

    //Fill the byte buffer with the binary representation of this instance
    command.toBytes(buf);

    //Send the byte buffer through the UDP connection
    connection.send(buf);

    //Notify BC_Bulletin so command information can be displayed on FSW tree
    emit commandSent(command.getAPID(), numberOfCommands);

}


//Create and send DOWNLINK_BUFFER
void BC_FSWCommand::downlink_buffer()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::DownlinkBuffer_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send PING
void BC_FSWCommand::ping()
{
    numberOfCommands++;

    isat_trek::Ping_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send COMM_SCHEDULE
void BC_FSWCommand::comm_schedule()
{
    numberOfCommands++;

    isat_trek::CommSchedule_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send TELEM_QUERY
void BC_FSWCommand::telem_query()
{    
    numberOfCommands++;

    buf.clear();

    isat_trek::TelemQuery_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send GNC
void BC_FSWCommand::gnc()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::ChangeMode_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send DECOM_COMMIT
void BC_FSWCommand::decom_commit()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::Decom_Commit_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send DEOCM_ENABLE
void BC_FSWCommand::decom_enable()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::Decom_Enable_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send PROP_SCHEDULE
void BC_FSWCommand::prop_schedule()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::PropSchedule_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send SAFE_MODE
void BC_FSWCommand::safe_mode()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::SafeMode_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send OPER_MODE
void BC_FSWCommand::oper_mode()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::OperMode_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send ABORT_COMM_PASS
void BC_FSWCommand::abort_comm_pass()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::AbortCommPass_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Opens dialog window to allow user to fill CAMERA_CAPTURE_IMG command parameters
void BC_FSWCommand::camera_capture_img() {cameraCaptureImgWindow->exec();}

//Create and send CAMERA_CAPTURE_IMG
void BC_FSWCommand::send_camera_capture_img(int avgBrightness, int fill)
{
    numberOfCommands++;

    buf.clear();

    isat_trek::CameraCaptureImg_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.avgBrightness = avgBrightness;
    command.fill = fill;

    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Opens dialog window to allow user to fill CAMERA_DOWNLOAD_IMGS command parameters
void BC_FSWCommand::camera_download_imgs() {cameraDownloadImgsWindow->exec();}

//Create and send CAMERA_DOWNLOAD_IMGS
void BC_FSWCommand::send_camera_download_imgs(int numImages)
{
    numberOfCommands++;

    buf.clear();

    isat_trek::CameraDownloadImgs_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.numImages = numImages;

    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send SET_DEV_AVAIL
void BC_FSWCommand::set_dev_avail()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::SetDevAvail_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send SET_DEV_POWER
void BC_FSWCommand::set_dev_power()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::SetDevPower_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send RESET_DEV
void BC_FSWCommand::reset_dev()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::ResetDev_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send FSW_RESTART
void BC_FSWCommand::fsw_restart()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::FSWRestart_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send FSW_REBOOT
void BC_FSWCommand::fsw_reboot()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::FSWReboot_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send TRANSMIT_DATA_RATE
void BC_FSWCommand::transmit_data_rate()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::TransmitDataRate_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//Create and send EVENT_RETRANS
void BC_FSWCommand::event_retrans()
{
    numberOfCommands++;

    buf.clear();

    isat_trek::EventRetrans_Command command;
    command.LDP_ENDPOINT = numberOfCommands;
    command.toBytes(buf);
    connection.send(buf);

    emit commandSent(command.getAPID(), numberOfCommands);
}

//This is the slot that will send command packets originating outside of the application (ex. from Jamie)
void BC_FSWCommand::takeOther(ByteBuffer buf)
{
    numberOfCommands++;

    buf.clear();

    //deserialize header, find apid and lastCommand, then just send buffer, don't worry about class?
    buf.putBits(104, 8, numberOfCommands);
    connection.send(buf);

    int apid;
    buf.getBits(5, 11, apid);

    emit commandSent(apid, numberOfCommands);
}

//"Lights" telemetry activity light if telemetry pdu is received
void BC_FSWCommand::pduReceived()
{
    delete telActLight;
    telActLight = telAct->addEllipse(0,0,20,20,QPen(QColor(0,0,0)),QBrush(QColor(50,200,50)));

    telActTimer->start(5000);
}

//"Turns off" telemetry activity light if no telemetry pdu is received for 5 seconds
void BC_FSWCommand::telActOff()
{
    delete telActLight;
    telActLight = telAct->addEllipse(0,0,20,20,QPen(QColor(0,0,0)),QBrush(QColor(200,50,50)));
    ui->RSSI->display(0);
}

void BC_FSWCommand::displayRSSI(int value)
{
    ui->RSSI->display(value);
}
