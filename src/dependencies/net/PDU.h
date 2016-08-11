#ifndef PDU_H
#define PDU_H

#include "../dependencies/net/EndPoint.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_net;

class PDU
{
   public:

      EndPoint source;
      EndPoint destination;

      ByteBuffer data;
};

#endif // PDU_H
