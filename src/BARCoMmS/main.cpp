#include "../modules/BARCoMmS_Command/bc_fswcommand.h"
#include "../modules/BARCoMmS_Bulletin/bc_bulletin.h"
#include "../modules/BARCoMmS_Camera/barcomms_camera.h"
#include "../modules/BARCoMmS_CFDP/barcomms_cfdp.h"
#include "../modules/BARCoMmS_DITL/bc_ditl.h"

#include "../dependencies/bc_PacketListenerThread.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Application object
    QApplication barcomms(argc, argv);

    // Load stylesheet
    QFile ssf(QString(RESOURCE_LOCATION).append("ss.qss"));
    ssf.open(QFile::ReadOnly);
    QString ss = QLatin1String(ssf.readAll());
    barcomms.setStyleSheet(ss);

    /*  Number of users who care about PDUs.
     *  Current users:
     *      (1) DITL
     *      (2) Bulletin
     *      (3) Command
     */
    //uint_fast8_t users = 2;

    // Packet listener worker thread
    BC_PacketListenerThread *plt11 = new BC_PacketListenerThread(3, 1111);
    BC_PacketListenerThread *plt14 = new BC_PacketListenerThread(1, 1114);

    // Application module objects
    BC_FSWCommand fswcommand;
    BC_Bulletin bulletin;
    // BARCoMmS_Camera camera;
    BARCoMmS_CFDP cfdp;
    BC_DITL ditl;

    // Packet user connections
    QObject::connect(plt11,SIGNAL(pduEmit(ByteBuffer)),&ditl,SLOT(pduReceived(ByteBuffer)));
    QObject::connect(plt11, SIGNAL(pduEmit(ByteBuffer)), &bulletin, SLOT(pduReceived(ByteBuffer)));
    QObject::connect(plt11, SIGNAL(pduEmit(ByteBuffer)), &fswcommand, SLOT(pduReceived()));

    // Bulletin -> Command connection
    QObject::connect(&bulletin, SIGNAL(rssi(int)), &fswcommand, SLOT(displayRSSI(int)));

    // CFDP -> Bulletin connection
    QObject::connect(&cfdp, SIGNAL(toBulletin(char *)), &bulletin, SLOT(takeCFDP(char *)));

    // Command -> Bulletin connection
    QObject::connect(&fswcommand, SIGNAL(commandSent(int, int)), &bulletin, SLOT(takeFSW(int, int)));

    // Jamie -> Command connection
    QObject::connect(plt14, SIGNAL(pduEmit(ByteBuffer)), &fswcommand, SLOT(takeOther(ByteBuffer)));

    // User death connections
    QObject::connect(&ditl,SIGNAL(dying()),plt11,SLOT(userDied()));
    QObject::connect(&bulletin, SIGNAL(dying()), plt11, SLOT(userDied()));
    QObject::connect(&fswcommand, SIGNAL(dying()), plt11, SLOT(userDied()));
    QObject::connect(&fswcommand, SIGNAL(dying()), plt14, SLOT(userDied()));

    // Show application modules
    fswcommand.show();
    bulletin.show();
    //camera.show();
    cfdp.show();
    ditl.show();

    // Start worker thread
    plt11->start();
    plt14->start();

    barcomms.exec();

    plt11->wait();
    plt14->wait();

    return 0;
}
