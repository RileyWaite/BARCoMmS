#ifndef HEALTHSTATUS_TELEMETRY_H
#define HEALTHSTATUS_TELEMETRY_H

#include "../dependencies/trek/AbstractTelemetryPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

class HealthStatus_Telemetry : public AbstractTelemetryPDU
{
   public:

      int mode;                         //   (32:8)    Current vehicle mode
      int lastCommand;                  //   (40:32)   Last Command id received
      int commandStatus;                //   (72:8)    Status of last command
      int decomEnabled;                 //   (80:8)    Decommission enabled.
      int decomInProg;                  //   (88:8)    Set to true after DECOM successfully received.
      int commPassesRem;                //   (96:8)    Comm passes remaining (including current pass, if any)
      int propEventRem;                 //   (104:8)   Propulsion events remaining.n
      int gncMode;                      //   (112:8)   GNC Mode
      int cmdSeqCnt;                    //   (120:16)  Cmd sequence count--note that this is 14 bits.
      int batterySOC;                   //   (136:32)  Battery status--will likely change.
      int receivedSigStr;               //   (168:8)   Signal strength as seen by receiver (dB)
      int camImgsPending;               //   (176:8)   Number of camera images available for download.


      HealthStatus_Telemetry();

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

#endif  // HEALTHSTATUS_TELEMETRY_H
