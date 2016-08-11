#ifndef BC_PACKETLISTENERTHREAD_H
#define BC_PACKETLISTENERTHREAD_H

#include <QObject>
#include <QThread>
#include "utils/String.h"
#include "net/UDPConnection.h"
#include "net/UDPConnectionListener.h"

#define HOST localhost
//#define PORT 1111

// Register meta type for signal emittion
Q_DECLARE_METATYPE(ByteBuffer)

class BC_PacketListenerThread : public QThread,
                                public UDPConnectionListener
{
    Q_OBJECT

signals:
    void pduEmit(ByteBuffer);

public slots:
    void userDied();

public:
    BC_PacketListenerThread(uint_fast8_t, int);

    void run();
    void pduReceived(UDPConnection&, PDU);

private:
    uint_fast8_t users;

    EndPoint *dest;
    UDPConnection conn;
    String ipAddr;
};

#endif // BC_PACKETLISTENERTHREAD_H
