
#ifndef PACKET_H
#define PACKET_H

#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;


namespace isat_trek
{

class Packet
{
   public:

      virtual bool toBytes(ByteBuffer& buf) = 0;
      
      virtual bool fromBytes(ByteBuffer& buf) = 0;
      
};

}

#endif // PACKET_H
