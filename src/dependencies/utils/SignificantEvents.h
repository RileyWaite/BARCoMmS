#ifndef SIGNIFICANTEVENTS_H
#define SIGNIFICANTEVENTS_H


namespace isat_utils
{

/**
 * Enumerations to define the id for each significant event. The ranges will correspond to the APID for each CSC like this:
 *
 *    start of sigevent id range = CSC Id * 100.
 *
 *
 */

enum SignificantEvents
   {
      // System Manager 100-199
      // Telemetry Subsystem  200-299
      // GNC Subsystem 300-399
      // Propulsion Subsystem 400-499
      // File Manager 500-599
      // Comm Manager 600-699
      // AuxBoard 700-799
      // EPS (Electrical Power System) 800-899
      // FlightComputer 900-999
      // GPS 1000-1099
      // IMU 1100-1199
      // IOBoard 1200-1299
      // Magnetometer 1300-1399
      // PPU 1400-1499
      // Reaction Wheels 1500-1599
      // StarTracker 1600-1699
      // Sun Sensor 1700-1799
      // Torque Rods 1800-1899
      // Transceiver 1900-1999
      // fswMain 2000-2099
      
   };

}  // namespace isat_utils

#endif // SIGNIFICANTEVENTS_H
