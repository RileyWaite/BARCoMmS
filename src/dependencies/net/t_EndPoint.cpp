#include "../dependencies/utils/String.h"
#include "../dependencies/net/EndPoint.h"

using namespace isat_utils;
using namespace isat_net;

String
getAddr(EndPoint ep)
{
   String tmp;
   if (ep.getIPAddress(tmp))
      return tmp;

   return String("NOPE");
}

int
main(int argc, char** argv)
{
   EndPoint ep;
   ep.setHost("slashdot.org");

   
   cout << getAddr(ep) << endl;

   EndPoint fc("127.0.0.1", 5432);

   cout << getAddr(fc) << endl;   

   EndPoint gg;
   gg.setHost("www.google.com");
   cout << getAddr(gg) << endl;

   EndPoint ggcopy(gg);
   cout << getAddr(ggcopy) << endl;   

   cout << "\nTesting getInetAddr() on www.google.com\n";
   struct in_addr foo;
   gg.getInetAddr(foo);
   cout << inet_ntoa(foo) << endl;
   
}
