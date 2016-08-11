
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "isat/utils/System.h"


namespace isat_utils
{

   
std::string
System::getEnv(std::string varName)
{
   std::string retval;

   char const* value = getenv(varName.c_str());
   if (value != 0)
      retval = value;

   return retval;
}


uint64_t
System::getTimeInMilliseconds()
{
    uint64_t          ms; // Milliseconds
    uint64_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = spec.tv_nsec / 1000000;

    return s * 1000 + ms;
}
   
} // namespace isat_utils

