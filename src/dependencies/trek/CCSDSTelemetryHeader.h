#ifndef CCSDSTELEMETRYHEADER_H
#define CCSDSTELEMETRYHEADER_H

#include "../dependencies/utils/ByteBuffer.h"

namespace isat_trek
{

/**
 * A CCSDSTelemetryHeader writes the required CCSDS Telemetry Header fields to the given
 * ByteBuffer. (Really.. did you expect anything else with a name like CCSDSTelemetryHeader?)
 */
class CCSDSTelemetryHeader
{
   public:

      int version;             // 0:3
      int ptype;               // 3:1
      int shf;                 // 4:1
      int apid;                // 5:11
      int seq_flags;           // 15:2
      int seq_count;           // 18:14
      int pkt_length;          // 32:16
      int coarse_time;         // 48:32
      int fine_time;           // 80:8
      int sp_source;           // 88:4
      int trek_seat;           // 92:4
      int ancil_data;          // 96:32

      // Write the header to the byte buffer, leaving the seek pointer positioned at the end.
      void toBytes(isat_utils::ByteBuffer& buf);

      void fromBytes(isat_utils::ByteBuffer& buf);
};

}  // namespace isat_trek

#endif  // CCSDSTELEMETRYHEADER_H
