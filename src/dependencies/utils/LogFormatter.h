#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

#include <string>
#include "isat/utils/Log.h"
#include "isat/utils/LogCommon.h"


namespace isat_utils
{

class LogFormatter
{
   public:

      virtual std::string getLogEntry(time_t entryTime,
                                      LogCommon::LogLevel logLevel,
                                      std::string loggerName,
                                      std::string message) = 0;
};

}  // namespace isat_utils

#endif // LOGFORMATTER_H
