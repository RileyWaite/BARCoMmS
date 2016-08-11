
#include "../dependencies/trek/telemetry/HealthStatus_Telemetry.h"

namespace isat_trek
{

HealthStatus_Telemetry::HealthStatus_Telemetry()
{
   mode = 0;
   lastCommand = 0;
   commandStatus = 0;
   decomEnabled = 0;
   decomInProg = 0;
   commPassesRem = 0;
   propEventRem = 0;
   gncMode = 0;
   cmdSeqCnt = 0;
   batterySOC = 0;
   receivedSigStr = 0;
   camImgsPending = 0;


   apid = 1;
}

bool
HealthStatus_Telemetry::fromBytes(ByteBuffer& buf)
{

   buf.getBits(32, 8, mode);
   buf.getBits(40, 32, lastCommand);
   buf.getBits(72, 8, commandStatus);
   buf.getBits(80, 8, decomEnabled);
   buf.getBits(88, 8, decomInProg);
   buf.getBits(96, 8, commPassesRem);
   buf.getBits(104, 8, propEventRem);
   buf.getBits(112, 8, gncMode);
   buf.getBits(120, 16, cmdSeqCnt);
   buf.getBits(136, 32, batterySOC);
   buf.getBits(168, 8, receivedSigStr);
   buf.getBits(176, 8, camImgsPending);


   return true;
}

bool
HealthStatus_Telemetry::toBytes(ByteBuffer& buf)
{
   // Reserve space for the fields.
  char zeros[23] = {};

  //buf.clear();
  buf.put(zeros, 23);


   buf.putBits(32, 8, mode);
   buf.putBits(40, 32, lastCommand);
   buf.putBits(72, 8, commandStatus);
   buf.putBits(80, 8, decomEnabled);
   buf.putBits(88, 8, decomInProg);
   buf.putBits(96, 8, commPassesRem);
   buf.putBits(104, 8, propEventRem);
   buf.putBits(112, 8, gncMode);
   buf.putBits(120, 16, cmdSeqCnt);
   buf.putBits(136, 32, batterySOC);
   buf.putBits(168, 8, receivedSigStr);
   buf.putBits(176, 8, camImgsPending);


   return true;
}

}  // namespace isat_trek

