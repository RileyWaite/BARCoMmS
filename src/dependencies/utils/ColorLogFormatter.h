
#ifndef COLORLOGFORMATTER_H
#define COLORLOGFORMATTER_H

#include "../dependencies/utils/Log.h"
#include "../dependencies/utils/LogFormatter.h"
#include "../dependencies/utils/LogCommon.h"

namespace isat_utils
{
   
class ColorLogFormatter : public LogFormatter
{
   public:

      ColorLogFormatter();
      
      std::string getLogEntry(time_t entryTime, LogCommon::LogLevel logLevel, std::string loggerName, std::string message);

      void enableColor(bool flag);
      
   protected:

      bool colorEnabled;

      char const* normal_text;
      char const* bold_text;
      char const* red_text;
      char const* green_text;
      char const* yellow_text;
      char const* blue_text;
      char const* magenta_text;
      char const* cyan_text;
      char const* white_text;
      char const* defcolor;

      
};

}  // namespace isat_utils

#endif // COLORLOGFORMATTER_H
