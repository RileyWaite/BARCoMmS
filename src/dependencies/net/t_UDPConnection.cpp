#include "../dependencies/net/UDPConnectionListener.h"
#include "../dependencies/net/UDPConnection.h"
#include "../dependencies/utils/String.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


using namespace std;
using namespace isat_utils;

struct TestPacket
{
   public:

      int type;
      int data;
};

/**
 * This is both a client and a server. Used to test UDPConnection.
 *
 *
 * Usage:
 *
 * As server, takes one command line option (the port to listen on):
 *
 *    t_UDPConnection 5432
 *
 * will start a server listening on port 5432 on the current host.
 *
 *
 * As a client, takes two command line options, the host to connect to and the port
 * to connect to:
 *
 *   t_UDPConnection 127.0.0.1 5432
 *
 * will start the client and begin sending packets to the specified host/port.n
 */

void
printBuffer(ByteBuffer& buf)
{
   const char* foo = buf.getBytes();
   for (int i = 0; i < buf.getLimit(); i++)
   {
      if ((i > 0) && ((i % 2) == 0))
         printf(" ");
      
      printf("%02x", (unsigned char) foo[i]);
   }
   printf("\n");
}

class TestListener : public UDPConnectionListener
{
   public:

      void pduReceived(UDPConnection& conn, PDU pdu)
      {
         printBuffer(pdu.data);

         pdu.data.setByteOrder(ByteBuffer::LittleEndian);         
         TestPacket packet;
         pdu.data.seek(0);
         pdu.data.getInt(packet.type);
         pdu.data.getInt(packet.data);

         cout << "   Packet type: " << packet.type << endl;
         cout << "   Packet data: " << packet.data << endl;
      }
};

void
doClient(int argc, char** argv)
{
   EndPoint dest(argv[1], atoi(argv[2]));

   String ipAddress;
   if (!dest.getIPAddress(ipAddress))
   {
      cout << "Huh? What is '" << argv[1] << "'?\n";
      exit(1);
   }

   UDPConnection conn;
   if (!conn.create(EndPoint()))
   {
      cout << "Trouble creating UDPConnection. Exiting.\n";
      exit(1);
   }

   conn.setDestEndPoint(dest);
   
   cout << "Client sending to " << ipAddress << ":" << dest.getPort() << endl;

   ByteBuffer buf;
   buf.setByteOrder(ByteBuffer::LittleEndian);
   
   TestPacket tp;
   tp.type = 12;
   tp.data = 0;

   while (true)
   {
      cout << "Sending..\n";

      buf.clear();
      buf.putInt(tp.type);
      buf.putInt(tp.data++);
      
      conn.send(buf);
      printBuffer(buf);
      
      usleep(500000);
   }
}

void
doServer(int argc, char** argv)
{
   EndPoint serverEndpoint(atoi(argv[1]));

   String ipAddress;
   if (!serverEndpoint.getIPAddress(ipAddress))
   {
      cout << "Couldn't bind to server address on port " << serverEndpoint.getPort() << endl;
      exit(1);
   }

   UDPConnection conn;
   if (!conn.create(serverEndpoint))
   {
      cout << "Failed to create server connection.\n";
      exit(1);
   }

   TestListener tl;
   conn.addListener(&tl);
   
   cout << "Server receiving on " << ipAddress << ":" << serverEndpoint.getPort() << endl;

   while (true)
   {
      while (conn.process());
      sleep(3);
   }
}

int
main(int argc, char** argv)
{
   if ((argc < 2) || (argc > 3))
   {
      cout << "Usage:\nServer: t_UDPConnection <port>\nClient: t_UDPConnection <host> <port>\n";
      exit(0);
   }

   if (argc == 2)
      doServer(argc, argv);
   else
      doClient(argc, argv);
}
