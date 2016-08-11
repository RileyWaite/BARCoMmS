#ifndef GNC1_TELEMETRY_H
#define GNC1_TELEMETRY_H

#include "../dependencies/trek/AbstractTelemetryPDU.h"
#include "../dependencies/utils/ByteBuffer.h"

using namespace isat_utils;

namespace isat_trek
{

class GNC1_Telemetry : public AbstractTelemetryPDU
{
   public:

      int wEstX;                        //   (32:32)   Estimated Body Rate(x) rad/s
      int wEstY;                        //   (64:32)   Estimated Body Rate(y) rad/s
      int wEstZ;                        //   (96:32)   Estimated Body Rate(z) rad/s
      int attValid;                     //   (128:8)   Attitude Filter Valid Flag
      int attMeasAvail;                 //   (136:8)   Attitude Measurements Available
      int rwCmdTorqueX;                 //   (144:32)  Reaction Wheel Torque(x) Nm
      int rwCmdTorqueY;                 //   (176:32)  Reaction Wheel Torque(y) Nm
      int rwCmdTorqueZ;                 //   (208:32)  Reaction Wheel Torque(z) Nm
      int trqCmdDipoleX;                //   (240:32)  Torque Coils Dipole(x)
      int trqCmdDipoleY;                //   (272:32)  Torque Coils Dipole(y)
      int trqCmdDipoleZ;                //   (304:32)  Torque Coils Dipole(z)
      int gncMode;                      //   (336:8)   GNC Operation Mode
      int gncSubmode;                   //   (344:8)   Guidance Submode
      int enableMM;                     //   (352:8)   Enable Momentum Management
      int validCmdFlag;                 //   (360:8)   Valid Command Flag
      int navValidFlag;                 //   (368:8)   Navigation Filter Valid Flag
      int tCur;                         //   (376:32)  Current Time T2010


      GNC1_Telemetry();

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

#endif  // GNC1_TELEMETRY_H
