#ifndef TELEMETRYIDS_H
#define TELEMETRYIDS_H

namespace isat_trek
{

class TelemetryIds 
{
   public:

      enum Telemetry
      {
         HEALTHSTATUS = 1,
         GNC1 = 2,
         EVENT = 3
      };
};

} // namespace isat_trek

#endif  // TELEMETRYIDS_H
