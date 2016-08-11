
#include "../dependencies/trek/telemetry/GNC1_Telemetry.h"

namespace isat_trek
{

GNC1_Telemetry::GNC1_Telemetry()
{
   wEstX = 0;
   wEstY = 0;
   wEstZ = 0;
   attValid = 0;
   attMeasAvail = 0;
   rwCmdTorqueX = 0;
   rwCmdTorqueY = 0;
   rwCmdTorqueZ = 0;
   trqCmdDipoleX = 0;
   trqCmdDipoleY = 0;
   trqCmdDipoleZ = 0;
   gncMode = 0;
   gncSubmode = 0;
   enableMM = 0;
   validCmdFlag = 0;
   navValidFlag = 0;
   tCur = 0;


   apid = 2;
}

bool
GNC1_Telemetry::fromBytes(ByteBuffer& buf)
{

   buf.getBits(32, 32, wEstX);
   buf.getBits(64, 32, wEstY);
   buf.getBits(96, 32, wEstZ);
   buf.getBits(128, 8, attValid);
   buf.getBits(136, 8, attMeasAvail);
   buf.getBits(144, 32, rwCmdTorqueX);
   buf.getBits(176, 32, rwCmdTorqueY);
   buf.getBits(208, 32, rwCmdTorqueZ);
   buf.getBits(240, 32, trqCmdDipoleX);
   buf.getBits(272, 32, trqCmdDipoleY);
   buf.getBits(304, 32, trqCmdDipoleZ);
   buf.getBits(336, 8, gncMode);
   buf.getBits(344, 8, gncSubmode);
   buf.getBits(352, 8, enableMM);
   buf.getBits(360, 8, validCmdFlag);
   buf.getBits(368, 8, navValidFlag);
   buf.getBits(376, 32, tCur);


   return true;
}

bool
GNC1_Telemetry::toBytes(ByteBuffer& buf)
{
   // Reserve space for the fields.
  char zeros[51] = {};

  //buf.clear();
  buf.put(zeros, 51);


   buf.putBits(32, 32, wEstX);
   buf.putBits(64, 32, wEstY);
   buf.putBits(96, 32, wEstZ);
   buf.putBits(128, 8, attValid);
   buf.putBits(136, 8, attMeasAvail);
   buf.putBits(144, 32, rwCmdTorqueX);
   buf.putBits(176, 32, rwCmdTorqueY);
   buf.putBits(208, 32, rwCmdTorqueZ);
   buf.putBits(240, 32, trqCmdDipoleX);
   buf.putBits(272, 32, trqCmdDipoleY);
   buf.putBits(304, 32, trqCmdDipoleZ);
   buf.putBits(336, 8, gncMode);
   buf.putBits(344, 8, gncSubmode);
   buf.putBits(352, 8, enableMM);
   buf.putBits(360, 8, validCmdFlag);
   buf.putBits(368, 8, navValidFlag);
   buf.putBits(376, 32, tCur);


   return true;
}

}  // namespace isat_trek

