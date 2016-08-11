#include "../dependencies/trek/telemetry/Event_Telemetry.h"

namespace isat_trek
{

Event_Telemetry::Event_Telemetry()
{
   timestamp = 0;
   type = 0;
   severity = 0;
   originId = 0;
   code = 0;
   message = 0;


   apid = 3;
}

bool
Event_Telemetry::fromBytes(ByteBuffer& buf)
{

   buf.getBits(32, 32, timestamp);
   buf.getBits(64, 8, type);
   buf.getBits(72, 8, severity);
   buf.getBits(80, 16, originId);
   buf.getBits(96, 16, code);
   buf.getBits(112, 32, message);


   return true;
}

bool
Event_Telemetry::toBytes(ByteBuffer& buf)
{
   // Reserve space for the fields.
  char zeros[18] = {};

  //buf.clear();
  buf.put(zeros, 18);


   buf.putBits(32, 32, timestamp);
   buf.putBits(64, 8, type);
   buf.putBits(72, 8, severity);
   buf.putBits(80, 16, originId);
   buf.putBits(96, 16, code);
   buf.putBits(112, 32, message);


   return true;
}

}  // namespace isat_trek

