
#include "../dependencies/trek/command/ChangeMode_Command.h"

namespace isat_trek
{

ChangeMode_Command::ChangeMode_Command()
{
   APID = 6;
}

bool
ChangeMode_Command::fromBytes(ByteBuffer& buf)
{
   buf.getBits(0, 3, VERSION);
   buf.getBits(3, 1, TYPE);
   buf.getBits(4, 1, SEC_HDR_FLAG);
   buf.getBits(5, 11, APID);
   buf.getBits(16, 2, SEQ_FLAGS);
   buf.getBits(18, 14, PKT_SEQ_COUNT);
   buf.getBits(32, 16, PKT_LENGTH);
   buf.getBits(48, 32, COARSE_TIME);
   buf.getBits(80, 8, FINE_TIME);
   buf.getBits(88, 2, TIME_ID);
   buf.getBits(90, 1, CHKWORD_IND);
   buf.getBits(91, 1, ZOE);
   buf.getBits(92, 4, PKT_TYPE);
   buf.getBits(96, 1, SPARE1);
   buf.getBits(97, 4, ELEMENT_ID);
   buf.getBits(101, 1, CMD_PACKET);
   buf.getBits(102, 2, SPARE2);
   buf.getBits(104, 8, LDP_ENDPOINT);
   buf.getBits(112, 16, SUBSET_ID);
   buf.getBits(128, 16, SPARE3);
   buf.getBits(144, 16, LEGAL_MODES);
   buf.getBits(160, 8, newMode);


   return true;
}

bool
ChangeMode_Command::toBytes(ByteBuffer& buf)
{
   // Reserve space for the fields.
   char zeros[21] = {};

   buf.clear();
   buf.put(zeros, 21);

   buf.putBits(0, 3, VERSION);
   buf.putBits(3, 1, TYPE);
   buf.putBits(4, 1, SEC_HDR_FLAG);
   buf.putBits(5, 11, APID);
   buf.putBits(16, 2, SEQ_FLAGS);
   buf.putBits(18, 14, PKT_SEQ_COUNT);
   buf.putBits(32, 16, PKT_LENGTH);
   buf.putBits(48, 32, COARSE_TIME);
   buf.putBits(80, 8, FINE_TIME);
   buf.putBits(88, 2, TIME_ID);
   buf.putBits(90, 1, CHKWORD_IND);
   buf.putBits(91, 1, ZOE);
   buf.putBits(92, 4, PKT_TYPE);
   buf.putBits(96, 1, SPARE1);
   buf.putBits(97, 4, ELEMENT_ID);
   buf.putBits(101, 1, CMD_PACKET);
   buf.putBits(102, 2, SPARE2);
   buf.putBits(104, 8, LDP_ENDPOINT);
   buf.putBits(112, 16, SUBSET_ID);
   buf.putBits(128, 16, SPARE3);
   buf.putBits(144, 16, LEGAL_MODES);
   buf.putBits(160, 8, newMode);


   return true;
}

}  // namespace isat_trek

