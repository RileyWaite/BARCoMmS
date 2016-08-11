
#include "isat/utils/DefaultLogFilter.h"


namespace isat_utils
{

DefaultLogFilter::DefaultLogFilter()
   : minLogLevel(LogCommon::ALL)
{
}

void
DefaultLogFilter::setMinimumLogLevel(LogCommon::LogLevel minLogLevel)
{
   this->minLogLevel = minLogLevel;
}
   
   
bool
DefaultLogFilter::checkEntry(LogCommon::LogLevel logLevel, std::string loggerName, std::string message)
{
   if (logLevel >= minLogLevel)
      return true;

   return false;
}
   
}
