
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../dependencies/net/EndPoint.h"
#include "../dependencies/utils/String.h"

using namespace isat_utils;

namespace isat_net
{

EndPoint::EndPoint()
   : goodEndpointFlag(true),
     host(String("")),
     port(0)
{
   inetAddr.s_addr = 0;
}

EndPoint::EndPoint(String thehost, int theport)
{
   goodEndpointFlag = false;
   port = theport;
   setHost(thehost);
}

EndPoint::EndPoint(int port)
{
   goodEndpointFlag = true;
   host = String("");
   this->port = port;

   inetAddr.s_addr = htonl(INADDR_ANY);
}

bool
EndPoint::setHost(String address)
{
   goodEndpointFlag = false;
   host = address;

   struct addrinfo hints, *servinfo;
   int rv;

   memset(&hints, 0, sizeof hints);
   hints.ai_family = AF_INET;
   hints.ai_socktype = 0;

   if ((rv = getaddrinfo(address.c_str(),
                         0,
                         &hints,
                         &servinfo)) != 0)
   {
      fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
      return false;
   }

   // For now (and maybe forever) just take the first entry.
   if (servinfo == 0)
      return false;

   inetAddr = ((sockaddr_in*) (servinfo->ai_addr))->sin_addr;
   //inetAddr.s_addr = htonl(inetAddr.s_addr);
   
   freeaddrinfo(servinfo); // all done with this structure

   goodEndpointFlag = true;
   
   return true;
}

String
EndPoint::getHost() const
{
   return host;
}

bool
EndPoint::setPort(int port)
{
   this->port = port;
   return true;
}

int
EndPoint::getPort() const
{
   return port;
}

bool
EndPoint::getIPAddress(String& ipaddress) const
{
   if (!goodEndpointFlag)
      return false;

   struct in_addr foo = inetAddr;
   ipaddress = String(inet_ntoa(foo));
   return true;
}

bool
EndPoint::getInetAddr(struct in_addr& addr) const
{
   if (!goodEndpointFlag)
      return false;

   addr = inetAddr;

   return true;
}

} // namespace isat_net
