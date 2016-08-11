#ifndef LOGFILTER_H
#define LOGFILTER_H

#include <string>
#include "../dependencies/utils/LogCommon.h"


namespace isat_utils
{
   
class LogFilter
{
   public:

      virtual bool checkEntry(LogCommon::LogLevel, std::string loggerName, std::string message) = 0;
         
};

} // namespace isat_utils


#endif // LOGFILTER_H
