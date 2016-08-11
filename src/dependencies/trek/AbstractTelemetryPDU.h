#ifndef ABSTRACTTELEMETRYPDU_H
#define ABSTRACTTELEMETRYPDU_H

#include "../dependencies/trek/Packet.h"
#include "../dependencies//utils/ByteBuffer.h"

using namespace isat_utils;


namespace isat_trek
{

class AbstractTelemetryPDU : public Packet
{
   public:

      int16_t apid;
      int64_t time;
      int32_t objectId;
      
      
      AbstractTelemetryPDU() {}

      virtual ~AbstractTelemetryPDU() {}
      
};

}  // namespace isat_trek

#endif // ABSTRACTTELEMETRYPDU_H
