
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "isat/utils/Utils.h"


namespace isat_utils
{

int64_t Utils::simulatedTime = 0;
int64_t Utils::systemTimeAtStart = 0;


bool
Utils::parseDateTime(std::string dateTime, long& time)
{
   struct tm timeStruct;
   
   if (strptime(dateTime.c_str(), "%Y-%m-%d %H:%M:%S%Z", &timeStruct) == 0)
      return false;

   long result = mktime(&timeStruct);
   if (result == -1)
      return false;

   time = result;
   
   return true;
}


int64_t
Utils::getSystemTimeInMillis()
{
   struct timespec ts;
   clock_gettime(CLOCK_REALTIME, &ts);

   int64_t curTime = static_cast<int64_t>(ts.tv_sec);
   curTime = (curTime * 1000) + (ts.tv_nsec / 1000000);

   // Adjust the real system time by any simulated time offset.
   curTime = simulatedTime + (curTime - systemTimeAtStart);
   
   return curTime;
}


void
Utils::sleepInMillis(int32_t millisecondsToSleep)
{
   struct timespec ts;
   ts.tv_sec = millisecondsToSleep / 1000;
   ts.tv_nsec = (millisecondsToSleep % 1000) * 1000000;

   nanosleep(&ts, 0);
}

void
Utils::setSimulatedTime(int64_t timeInMillis)
{
   simulatedTime = 0;
   systemTimeAtStart = 0;
   
   int64_t st = timeInMillis;
   int64_t sysStartTime = getSystemTimeInMillis();
   
   simulatedTime = st;
   systemTimeAtStart = sysStartTime;
}

std::string
Utils::format(std::string formatString, int val)
{
   char buf[1024];
   snprintf(buf, 1024, formatString.c_str(), val);

   return std::string(buf);
}

std::string
Utils::format(std::string formatString, float val)
{
   char buf[1024];
   snprintf(buf, 1024, formatString.c_str(), val);

   return std::string(buf);
}

std::string
Utils::format(std::string formatString, double val)
{
   char buf[1024];
   snprintf(buf, 1024, formatString.c_str(), val);

   return std::string(buf);
}

bool
Utils::parseInt(char const* str, long& value)
{
   char *endptr = 0;
   value = strtol(str, &endptr, 0);
   
   if (*endptr != '\0')
      return false;
   
   return true;
}

bool
Utils::parseDouble(char const* str, double& value)
{
   char *endptr = 0;
   value = strtod(str, &endptr);

   if (endptr == str)
      return false;

   return true;
}

bool
Utils::parseBool(char const* str, bool& value)
{
   if (str == 0)
   {
      value = false;
      return true;
   }

   if ((str[0] == 't') ||
       (str[0] == 'T') ||
       (str[0] == 'Y') ||
       (str[0] == '1'))
   {
      value = true;
      return true;
   }

   value = false;
   
   return true;
}


bool
Utils::parseHex(char const* str, long& value)
{
   char *endptr = 0;
   value = strtoul(str, &endptr, 0);
   
   if (*endptr != '\0')
      return false;
   
   return true;
}



}  // namespace isat_utils

