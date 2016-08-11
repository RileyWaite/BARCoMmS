
#ifndef LOG_H
#define LOG_H

#include <string>
#include "../dependencies/utils/LogFilter.h"
#include "../dependencies/utils/LogFormatter.h"
#include "../dependencies/utils/LogCommon.h"


namespace isat_utils
{
   
class Log
{
   public:

      
      Log();

      virtual void setLogFilter(LogFilter* logFilter);
      virtual LogFilter* getLogFilter();
      
      virtual void setLogFormatter(LogFormatter* logFormatter);
      virtual LogFormatter* getLogFormatter();
      
      virtual bool writeEntry(LogCommon::LogLevel logLevel, std::string loggerName,  std::string message);

   protected:

      LogFilter* logFilter;
      LogFormatter* logFormatter;
      
};

} // namespace isat_utils
   
#endif // LOG_H
