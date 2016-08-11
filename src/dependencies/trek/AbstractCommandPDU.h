#ifndef ABSTRACTCOMMANDPDU_H
#define ABSTRACTCOMMANDPDU_H

#include "../dependencies/utils/ByteBuffer.h"
#include "../dependencies/trek/Packet.h"

using namespace isat_utils;

namespace isat_trek
{

class AbstractCommandPDU : public Packet
{
   public:
      
      int VERSION = 0;                      // (0:3)     CCSDS Version Number
      int TYPE = 0;                         // (3:1)     CCSDS Type Bit
      int SEC_HDR_FLAG = 0;                 // (4:1)     CCSDS Secondary Header Flag
      int APID;                             // (5:11)    CCSDS APID
      int SEQ_FLAGS = 0;                    // (16:2)    CCSDS Sequence Flags
      int PKT_SEQ_COUNT = 0;                // (18:14)   CCSDS Packet Sequence Count
      int PKT_LENGTH = 0;                   // (32:16)   CCSDS Packet Length
      int COARSE_TIME = 0;                  // (48:32)   Secondary Header CCSDS Unsegmented Time (Coarse)
      int FINE_TIME = 0;                    // (80:8)    Secondary Header CCSDS Unsegmented Time (Fine)
      int TIME_ID = 0;                      // (88:2)    Secondary Header Time ID
      int CHKWORD_IND = 0;                  // (90:1)    Secondary Header Checkword Indicator
      int ZOE = 0;                          // (91:1)    Secondary Header ZOE Telemetry Flag
      int PKT_TYPE = 0;                     // (92:4)    Secondary Header Packet Type
      int SPARE1 = 0;                       // (96:1)    Secondary Header Spare1
      int ELEMENT_ID = 0;                   // (97:4)    Secondary Header Element ID
      int CMD_PACKET = 0;                   // (101:1)   Secondary Header CMD Indicator
      int SPARE2 = 0;                       // (102:2)   Secondary Header Spare2
      int LDP_ENDPOINT;                     // (104:8)   Secondary Header LDP Endpoint
      int SUBSET_ID = 0;                    // (112:16)  Secondary Header Subset ID
      int SPARE3 = 0;                       // (128:16)  Secondary Header Spare3
      int LEGAL_MODES = 0;                  // (144:16)  Secondary Header Legal Station Modes


      AbstractCommandPDU() {}
      virtual ~AbstractCommandPDU() {}
      
      
      int getAPID()
      {
         return APID;
      }

      int getTimeStamp()
      {
         return COARSE_TIME;
      }
}; 

}  // namespace isat_trek

#endif // ABSTRACTCOMMANDPDU_H 
