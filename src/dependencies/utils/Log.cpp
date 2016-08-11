
#include "isat/utils/Log.h"

namespace isat_utils
{

Log::Log()
   : logFilter(0),
     logFormatter(0)
{
}

   void
   Log::setLogFilter(LogFilter* logFilter)
   {
      this->logFilter = logFilter;
   }

   LogFilter*
   Log::getLogFilter()
   {
      return logFilter;
   }

   void
   Log::setLogFormatter(LogFormatter* logFormatter)
   {
      this->logFormatter = logFormatter;
   }

   LogFormatter*
   Log::getLogFormatter()
   {
      return logFormatter;
   }
   
   bool
   Log::writeEntry(LogCommon::LogLevel logLevel, std::string name, std::string message)
   {
      return false;
   }
   
} // namespace isat_utils
