#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <stdint.h>


namespace isat_utils
{

class Utils
{
   public:

      /**
       * Converts string representation of a date and time in the format "YYY-MM-DD HH:MM:SS" into seconds since unix epoch.
       *
       * @returns true If conversion was successful.
       */
      static bool parseDateTime(std::string dateTime, long& time);


      /**
       * Gets the system time in milliseconds since the unix epoch.
       *
       * @return time in milliseconds (unix epoch)
       */
      static int64_t getSystemTimeInMillis();


      static void sleepInMillis(int32_t millisecondsToSleep);
      
      /**
       * For testing purposes, it's handy to be able to always start
       * the flight software at the same time. setSimulatedTime() will
       * cause system time to be reported a if the system clock had
       * been set to timeInMillis at the time the method is called.
       */
      static void setSimulatedTime(int64_t timeInMillis);

      static std::string format(std::string formatString, int val);
      static std::string format(std::string formatString, float val);
      static std::string format(std::string formatString, double val);

      static bool parseInt(char const* str, long& value);
      static bool parseDouble(char const* str, double& value);
      static bool parseBool(char const* str, bool& value);
      static bool parseHex(char const* str, long& value);      

   private:

      static int64_t simulatedTime;        // Desired simulated system time
      static int64_t systemTimeAtStart;    // The real system time at the moment the simulated time was set.
};

} // namespace isat_utils

#endif // UTILS_H
