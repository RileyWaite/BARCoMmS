#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include "../dependencies/net/EndPoint.h"
#include "../dependencies/utils/ByteBuffer.h"
#include "../dependencies/net/UDPConnectionListener.h"
#include "../dependencies/utils/ArrayList.h"

using namespace isat_net;
using namespace isat_utils;


//namespace isat_net
//{

/**
 * Provides a UDP send / receive capability that uses the Observer
 * pattern to notify clients of received packets.
 */
class UDPConnection
{
   public:

      UDPConnection();
      ~UDPConnection();


      /**
       * Create a socket on the specified network interface and port.
       *
       * @param networkInterface - The IP address of the local network port, or null string for INADDR_ANY.
       * @param port - The port to bind to, or 0 for an ephemeral port.
       *
       * @return true if the socket was created successfully.
       */
      bool create(EndPoint src);

      void setDestEndPoint(EndPoint dest);

      bool send(ByteBuffer& byteBuf);

      void addListener(UDPConnectionListener* listener);

      /**
       * This implementation of UDPConnection does NOT contain worker threads. Call the process() method
       * periodically to check for incoming packets and notify listeners.
       * @return true if a packet was processed.
       */
      bool process();

   private:

      int udpSocket;
      EndPoint src;
      EndPoint dest;
      ArrayList<UDPConnectionListener*> listeners;

      char *packetBuf;  // Buffer to hold incoming packets until transferred to a PDU instance.
      static const int packetBufSize = 65535;
};

//}  // namespace isat_net


#endif // UDPCONNECTION_H

