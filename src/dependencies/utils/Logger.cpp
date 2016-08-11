#include <iostream>
#include <string>
#include "isat/utils/Logger.h"

namespace isat_utils
{

Logger::Logger(std::string loggerName)
   : name(loggerName),
     log(0)
{
}

void
Logger::setLog(Log* log)
{
   this->log = log;
}

void
Logger::debug(std::string message)
{
   if (log == 0)
      return;

   log->writeEntry(LogCommon::DEBUG, name, message);
}

void
Logger::info(std::string message)
{
   if (log == 0)
      return;

   log->writeEntry(LogCommon::INFO, name, message);   
}

void
Logger::warn(std::string message)
{
   if (log == 0)
      return;

   log->writeEntry(LogCommon::WARN, name, message);   
}

void
Logger::error(std::string message)
{
   if (log == 0)
      return;

   log->writeEntry(LogCommon::ERROR, name, message);   
}

void
Logger::fatal(std::string message)
{
   if (log == 0)
      return;

   log->writeEntry(LogCommon::FATAL, name, message);   
}

} // namespace isat_utils

