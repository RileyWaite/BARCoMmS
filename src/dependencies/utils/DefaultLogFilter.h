#ifndef DEFAULTLOGFILTER_H
#define DEFAULTLOGFILTER_H

#include <string>
#include "../dependencies/utils/LogCommon.h"
#include "../dependencies/utils/LogFilter.h"

namespace isat_utils
{

class DefaultLogFilter : public LogFilter
{
   public:

      DefaultLogFilter();
      
      void setMinimumLogLevel(LogCommon::LogLevel minLogLevel);
      
      bool checkEntry(LogCommon::LogLevel logLevel, std::string loggerName, std::string message);

      
   protected:

      LogCommon::LogLevel minLogLevel;
      
};

}  // namespace isat_utils


#endif // DEFAULTLOGFILTER_H
