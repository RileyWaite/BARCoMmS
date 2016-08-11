#ifndef BC_FSWCOMMAND_H
#define BC_FSWCOMMAND_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLCDNumber>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "../dependencies/net/UDPConnection.h"

#include "../dependencies/trek/command/AbortCommPass_Command.h"
#include "../dependencies/trek/command/CameraCaptureImg_Command.h"
#include "../dependencies/trek/command/CameraDownloadImgs_Command.h"
#include "../dependencies/trek/command/ChangeMode_Command.h"
#include "../dependencies/trek/command/CommSchedule_Command.h"
#include "../dependencies/trek/command/Decom_Commit_Command.h"
#include "../dependencies/trek/command/Decom_Enable_Command.h"
#include "../dependencies/trek/command/DownlinkBuffer_Command.h"
#include "../dependencies/trek/command/EventRetrans_Command.h"
#include "../dependencies/trek/command/FSWReboot_Command.h"
#include "../dependencies/trek/command/FSWRestart_Command.h"
#include "../dependencies/trek/command/FSW_Control_Command.h"
#include "../dependencies/trek/command/OperMode_Command.h"
#include "../dependencies/trek/command/Ping_Command.h"
#include "../dependencies/trek/command/PropSchedule_Command.h"
#include "../dependencies/trek/command/ResetDev_Command.h"
#include "../dependencies/trek/command/SafeMode_Command.h"
#include "../dependencies/trek/command/SetDevAvail_Command.h"
#include "../dependencies/trek/command/SetDevPower_Command.h"
#include "../dependencies/trek/command/TelemQuery_Command.h"
#include "../dependencies/trek/command/TransmitDataRate_Command.h"

#include "camera_capture_img_window.h"
#include "camera_download_imgs_window.h"

namespace Ui {
class BC_FSWCommand;
}

class BC_FSWCommand : public QMainWindow
{
    Q_OBJECT

public:
    explicit BC_FSWCommand(QWidget *parent = 0);
    ~BC_FSWCommand();

    //Displays informative window (exit)
    void closeEvent(QCloseEvent*);

    //Objects necessary to support communication with FSW via UDP port
    UDPConnection connection;
    EndPoint src;
    EndPoint dest;
    ByteBuffer buf;

    //Informative dialog window to inform user they are exiting the program
    QMessageBox *msgExit;

    //Stores number of commands sent so sequential IDs can be created
    int numberOfCommands;
    QFile cmdSeqIdFile;

    //Dialog windows to fill in command parameters
    Camera_Capture_Img_Window *cameraCaptureImgWindow;
    Camera_Download_Imgs_Window *cameraDownloadImgsWindow;

    //Instantiates the QLCDNumber display for the received signal strength
    QLCDNumber *RSSI;

    //QGraphicsScene to hold telemety activity light, QGraphicsEllipseItem to be the light, QTimer to
    // turn the light off after so long without telemetry
    QGraphicsScene *telAct;
    QGraphicsEllipseItem *telActLight;
    QTimer *telActTimer = new QTimer();

public slots:

    /*Create and send command packets as defined in Data Dictionary 7/5/2016
    * Currently support 21 commands in "Commmands" tab
    * Commands without parameters can stay like this,
    * Commands with parameter can follow the format of CAMERA_CAPTURE_IMG or CAMERA_DOWNLOAD_IMGS (see below)
    */
    void fsw_command();
    void downlink_buffer();
    void ping();
    void comm_schedule();
    void telem_query();
    void gnc();
    void decom_commit();
    void decom_enable();
    void prop_schedule();
    void safe_mode();
    void oper_mode();
    void abort_comm_pass();
    void set_dev_avail();
    void set_dev_power();
    void reset_dev();
    void fsw_restart();
    void fsw_reboot();
    void transmit_data_rate();
    void event_retrans();

    //Opens dialog for user to input command parameters
    void camera_capture_img();
    //Creates and sends command
    void send_camera_capture_img(int, int);

    //Opens dialog for user to input command parameters
    void camera_download_imgs();
    //Creates and sends command
    void send_camera_download_imgs(int);

    //Send command originating outside of this application (ex. from Jamie)
    void takeOther(ByteBuffer);

    //Displays the received signal strength from the health and status packet
    void displayRSSI(int);

    //"Lights" telemetry activity light if telemetry pdu is received
    void pduReceived();

    //"Turns off" telemetry activity light if no telemetry pdu is received for 5 seconds
    void telActOff();

signals:

    //Emit signal to BC_Bulletin so command information can be displayed on FSW tree
    void commandSent(int apid, int id);

    //Emitted when Command window is closed, tells Packet Listener Thread that it is no longer being used
    void dying();

private:
    Ui::BC_FSWCommand *ui;   

};

#endif // BC_FSWCOMMAND_H
