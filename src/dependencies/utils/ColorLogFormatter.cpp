#include <stdlib.h>
#include <time.h>
#include "../dependencies/utils/ColorLogFormatter.h"

#define NORMAL_TEXT   "\033[0m"
#define BOLD_TEXT     "\033[1m"
#define RED_TEXT      "\033[31m"
#define GREEN_TEXT    "\033[32m"
#define YELLOW_TEXT   "\033[33m"
#define BLUE_TEXT     "\033[34m"
#define MAGENTA_TEXT  "\033[35m"
#define CYAN_TEXT     "\033[36m"
#define WHITE_TEXT    "\033[37m"
#define DEFCOLOR      "\033[39m"


namespace isat_utils
{

   ColorLogFormatter::ColorLogFormatter()
      : colorEnabled(false)
   {
   }

   
   void
   ColorLogFormatter::enableColor(bool flag)
   {
      colorEnabled = flag;

      if (colorEnabled)
      {
         normal_text = NORMAL_TEXT;
         bold_text = BOLD_TEXT;
         red_text = RED_TEXT;
         green_text = GREEN_TEXT;
         yellow_text = YELLOW_TEXT;
         blue_text = BLUE_TEXT;
         magenta_text = MAGENTA_TEXT;
         cyan_text = CYAN_TEXT;
         white_text = WHITE_TEXT;
         defcolor = DEFCOLOR;
      }
      else
      {
         normal_text = "";
         bold_text = "";
         red_text = "";
         green_text = "";
         yellow_text = "";
         blue_text = "";
         magenta_text = "";
         cyan_text = "";
         white_text = "";
         defcolor = "";
      }
   }

   
std::string
ColorLogFormatter::getLogEntry(time_t entryTime, LogCommon::LogLevel logLevel, std::string loggerName, std::string message)
{
   struct tm timefields;
   gmtime_r(&entryTime, &timefields);

   char tbuf[100];
   strftime(tbuf, 100, "%F %T", &timefields);


   std::string entry;
   entry = entry + normal_text + white_text;
   entry = entry + tbuf + defcolor;
   entry = entry + cyan_text;
   entry = entry + " [";
   entry = entry + loggerName;
   entry = entry +  "] " + defcolor;

   switch (logLevel)
   {
      case LogCommon::DEBUG:
         entry = entry + blue_text + "(DEBUG) "; break;
      case LogCommon::INFO:
         entry = entry + green_text + "(INFO) ";  break;
      case LogCommon::WARN:
         entry = entry + yellow_text + bold_text + "(WARN) ";  break;
      case LogCommon::ERROR:
         entry = entry + red_text + "(ERROR) "; break;
      case LogCommon::FATAL:
         entry = entry + red_text + bold_text + "(FATAL) "; break;
         
      case LogCommon::ALL:
      case LogCommon::OFF:
      default: break;
   }

   entry = entry + message + normal_text;

   return entry;

}

} // namespace isat_utils
