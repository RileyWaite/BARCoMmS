#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <arpa/inet.h>
#include "../dependencies/utils/String.h"

using namespace isat_utils;


namespace isat_net
{

   /**
    * An Endpoint represents an (ip address, port) tuple. The host can
    * be either a hostname or ip address in the dotted quad format.
    */
class EndPoint
{
   public:

      EndPoint();
      EndPoint(String host, int port = 0);
      EndPoint(int port);
      
      /**
       * Set the host for this end point, as either a hostname or dotted quad ("192.168.6.3").
       *
       * @return true if the host is valid (a host name resolves to an
       * ip address or correctly format dotted quad.)
       */
      bool setHost(String address);
      String getHost() const;

      /**
       * Port must be in range [0, 65535].
       */
      bool setPort(int port);
      int getPort() const;

      /**
       * Get the ip address for the current host.
       *
       * @return true if the current host is valid (has an ip address).
       */
      bool getIPAddress(String& ipAddress) const;


      /**
       * Convert the current host address into a binary representation (inet_aton).
       *
       * @return true if the address converted.
       */
      bool getInetAddr(struct in_addr& addr) const;

      
   private:

      bool goodEndpointFlag;
      String host;
      int port;
      struct in_addr inetAddr;
};

}  // namespace isat_net

#endif // ENDPOINT_H
