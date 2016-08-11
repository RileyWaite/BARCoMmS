#ifndef EVENT_TELEMETRY_H
#define EVENT_TELEMETRY_H

#include "../dependencies/trek/AbstractTelemetryPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

class Event_Telemetry : public AbstractTelemetryPDU
{
   public:

      int timestamp;                    //   (32:32)   Unix epoch time event occured
      int type;                         //   (64:8)    Event Type: 0 == point, 1 == begin,  2 == end
      int severity;                     //   (72:8)    0 = Advisory, 1 == Caution, 2 == Warning
      int originId;                     //   (80:16)   Unique id assigned to things that can issue events.
      int code;                         //   (96:16)   Event code. Indexes into table of event descriptions.
      int message;                      //   (112:32)  This should be char[40] with a null terminated string.


      Event_Telemetry();

      /**
       * Populate the header and command fields from the data in buf.
       *
       * @return true if successful.
       */
      virtual bool fromBytes(ByteBuffer& buf);

      /** 
       * Create the binary representation of this instance in the specified buffer.
       * 
       * @return true if successful.
       */
      virtual bool toBytes(ByteBuffer& buf);
};

} // namespace isat_trek

#endif  // EVENT_TELEMETRY_H
