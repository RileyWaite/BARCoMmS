#include "bc_PacketListenerThread.h"

#include <QDebug>

inline void wtPrint(std::string msg){ fprintf(stderr, "\033[1;36mWorker Thread\033[0;30m: %s\n", msg.c_str()); }

BC_PacketListenerThread::BC_PacketListenerThread(uint_fast8_t users, int PORT)
{
    // Assign user count
    this->users = users;

    // Set listening port
    dest = new EndPoint(PORT);

    // Error checks
    if(!dest->getIPAddress(ipAddr)) wtPrint("\033[1;31mFailed IP: It's a damn String!!\033[0;30m");
    if(!conn.create(*dest)) wtPrint("\033[1;31mTrouble creating UDPConnection.\033[0;30m");

    // Add self as listener
    conn.addListener(this);

    // Register meta type for signal emittion
    qRegisterMetaType<ByteBuffer>();
}

// Decrement user count when one dies
void BC_PacketListenerThread::userDied() { --users; }

// Called when a PDU is received (duh...)
void BC_PacketListenerThread::pduReceived(UDPConnection& conn, PDU pdu)
{
    wtPrint("Packet received");
    ByteBuffer buf(pdu.data);
    emit pduEmit(buf);
}

// Thread loop
void BC_PacketListenerThread::run()
{
    /* temp */ bool ff=1;
    for(;;)
    {
        // If nobody cares about the thread anymore, kill it
        if(users==0) break;

        conn.process();
        QThread::msleep(200);

        // ======= TEMP ======= //
        if(ff)
        {
            //wtPrint("FLIP");
            ff=0;
        }
        else
        {
            //wtPrint("FLOP");
            ff=1;
        }
    }
    //wtPrint("\033[1;31mQuitting Thread...\033[0;30m");
    this->quit();
}

