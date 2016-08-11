#ifndef UDPCONNECTIONLISTENER_H
#define UDPCONNECTIONLISTENER_H

#include "../dependencies/net/PDU.h"

class UDPConnection;
   
/**
 * Registered on a UDPConnection object, instances of this class are
 * notified when a PDU is received.
 */
class UDPConnectionListener
{
   public:

      virtual void pduReceived(UDPConnection& conn, PDU pdu) = 0;
};


#endif // UDPCONNECTIONLISTENER_H
