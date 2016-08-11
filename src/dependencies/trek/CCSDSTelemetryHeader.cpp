
#include "../dependencies/trek/CCSDSTelemetryHeader.h"


namespace isat_trek
{

void
CCSDSTelemetryHeader::toBytes(isat_utils::ByteBuffer &buf)
{
   // XXX: Until the final header is decided, let's just do apid.
   buf.clear();
   buf.putInt(apid);

#if 0   
   buf.clear();
   buf.putBits(0, 3, version);
   buf.putBits(3, 1, ptype);
   buf.putBits(4, 1, shf);
   buf.putBits(5, 11, apid);
   buf.putBits(16, 2, seq_flags);
   buf.putBits(18, 14, seq_count);
   buf.putBits(32, 16, pkt_length);
   buf.putBits(48, 32, coarse_time);
   buf.putBits(80, 8, fine_time);
   buf.putBits(88, 1, chkword);
   buf.putBits(89, 1, zoe);
   buf.putBits(90, 4, stype);
   buf.putBits(94, 16, versionId);
   buf.putBits(110, 16, dc_counter);
#endif   
}

void
CCSDSTelemetryHeader::fromBytes(isat_utils::ByteBuffer& buf)
{
   buf.seek(0);
   buf.getInt(apid);
}

}  // namespace isat_trek
