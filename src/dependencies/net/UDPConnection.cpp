
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include "../dependencies/net/UDPConnection.h"

UDPConnection::UDPConnection()
   : udpSocket(0),
     packetBuf(0)
{
   // Allocate a buffer to hold udp packets when we first receive them.
   packetBuf = new (std::nothrow) char[packetBufSize];
}

UDPConnection::~UDPConnection()
{
   if (udpSocket != 0)
   {
      close(udpSocket);
      udpSocket = 0;
   }

   if (packetBuf != 0)
   {
      delete [] packetBuf;
      packetBuf = 0;
   }
}

bool
UDPConnection::create(EndPoint src)
{
   this->src = src;

   udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
   if (udpSocket < 0)
   {
      cout << "Couldn't create socket.\n";
      return false;
   }

   struct in_addr src_addr;
   if (!src.getInetAddr(src_addr))
   {
      cout << "Couldn't get inetAddr from endpoint.\n";
      return false;
   }

   struct sockaddr_in myaddr;
   memset((char *)&myaddr, 0, sizeof(myaddr));
   myaddr.sin_family = AF_INET;
   myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   // cout << "*******" << inet_ntoa(myaddr.sin_addr) << "\n";
   myaddr.sin_port = htons(src.getPort());
   
   if (bind(udpSocket, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
   {
      perror("bind failed");
      return false;
   }   

   return true;
}

void
UDPConnection::setDestEndPoint(EndPoint dest)
{
   this->dest = dest;
}

bool
UDPConnection::send(ByteBuffer& byteBuf)
{
   struct sockaddr_in destAddr;
   
   memset((char*) &destAddr, sizeof(destAddr), 0);
   destAddr.sin_family = AF_INET;
   destAddr.sin_port   = htons(dest.getPort());
   dest.getInetAddr(destAddr.sin_addr);

   int rc = sendto(udpSocket, byteBuf.getBytes(), byteBuf.getPosition(), 0,
                   (struct sockaddr *) &destAddr, sizeof(destAddr));
   if (rc < 0)
   {
      perror("UDPConnection::send() ");
      return false;
   }
   
   return true;
}

void
UDPConnection::addListener(UDPConnectionListener* listener)
{
   listeners.add(listener);
}

bool
UDPConnection::process()
{
   fd_set read_fds;
   FD_ZERO(&read_fds);
   FD_SET(udpSocket, &read_fds);
   
   struct timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   
   struct sockaddr_in remoteAddr;
   socklen_t remoteAddrLength = sizeof(remoteAddr);

   int retval = select(udpSocket + 1, &read_fds, NULL, NULL, &tv);
   if (retval > 0)
   {
      int rc = recvfrom(udpSocket, packetBuf, packetBufSize, 0,
                        (struct sockaddr *) &remoteAddr, &remoteAddrLength);

      PDU pdu;
      pdu.data = ByteBuffer(rc);
      pdu.data.seek(0);
      pdu.data.put(packetBuf, rc);
         
      for (int i = 0; i < listeners.size(); i++)
      {
         UDPConnectionListener* l = 0;
         listeners.get(i,l);
         l->pduReceived(*this, pdu);
      }

      return true;
   }

   return false;
}

