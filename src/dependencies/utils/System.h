#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <string>

namespace isat_utils
{

/**
 * Various convenienve methods to get information about the system environment.
 */
class System
{
   public:

      /**
       * Get the value of an environment variable.
       *
       * @param varName The name of the environment variable.
       *
       * @return The value of the environment variable, or null string if not defined.
       */
        
      static std::string getEnv(std::string varName);

      static uint64_t getTimeInMilliseconds();
      
};


} // namespace isat_utils


#endif // SYSTEM_H








