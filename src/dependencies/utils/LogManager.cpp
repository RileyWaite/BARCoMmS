
#include "isat/utils/LogManager.h"
#include "isat/utils/ConsoleLog.h"

namespace isat_utils
{
   
LogManager::LogManager()
   : defaultLog(0)
{
}


LogManager::~LogManager()
{
   if (defaultLog != 0)
      delete defaultLog;
}

LogManager&
LogManager::getInstance()
{
   static LogManager instance;
   
   return instance;
}

   
bool
LogManager::addLog(String logName, Log* log)
{
   return false;
}

Log*
LogManager::getDefaultLog()
{
   if (defaultLog == 0)
      defaultLog = new ConsoleLog();

   return defaultLog;
}

Log*
LogManager::getLog(String logName)
{
   return 0;
}


}  // namespace isat_utils

