
#include "../dependencies/utils/Log.h"
#include "../dependencies/utils/LogCommon.h"

namespace isat_utils
{

class ConsoleLog : public isat_utils::Log
{
   public:

      ConsoleLog();
      ~ConsoleLog();

      bool writeEntry(LogCommon::LogLevel logLevel, std::string loggerName, std::string message);
};

}   // namespace isat_utils

