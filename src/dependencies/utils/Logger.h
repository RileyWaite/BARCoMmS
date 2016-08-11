#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "isat/utils/Log.h"

namespace isat_utils
{

class Logger
{
   public:

      Logger(std::string loggerName);

      void setLog(Log* log);

      void debug(std::string message);
      void info(std::string message);
      void warn(std::string message);
      void error(std::string message);
      void fatal(std::string message);

   protected:

      std::string name;
      Log* log;
};

} // namespace isat_utils

#endif // LOGGER_H
