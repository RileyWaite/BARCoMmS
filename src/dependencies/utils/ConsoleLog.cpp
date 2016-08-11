include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "isat/utils/ConsoleLog.h"
#include "isat/utils/LogFormatter.h"
#include "isat/utils/ColorLogFormatter.h"
#include "isat/utils/Utils.h"

using namespace std;

namespace isat_utils
{
   
ConsoleLog::ConsoleLog()
{
   ColorLogFormatter* clf = new ColorLogFormatter();
   clf->enableColor(false);
   

   // See if we're on a supported terminal type for color output.
   char* term = getenv("TERM");

   if (term != 0)
   {
      std::string terminalType(term);
      if ((terminalType == "xterm") || (terminalType == "xterm-256color"))
         clf->enableColor(true);
   }
   
   if (!isatty(fileno(stdout)))
   {
      clf->enableColor(false);
   }

   setLogFormatter(clf);
}

ConsoleLog::~ConsoleLog()
{
   if (logFormatter != 0)
      delete logFormatter;
}

   
bool
ConsoleLog::writeEntry(LogCommon::LogLevel logLevel, std::string loggerName, std::string message)
{
   //time_t curTime;
   //curTime = time(0);
   long curTime = Utils::getSystemTimeInMillis() / 1000;

   if (logFormatter == 0)
      return false;

   bool logIt = true;
   if (logFilter != 0)
   {
      logIt = logFilter->checkEntry(logLevel, loggerName, message);
   }
   
   if (logIt)
      cout << logFormatter->getLogEntry(curTime, logLevel, loggerName, message) << endl;

   return true;
}

}  // namespace isat_utils
