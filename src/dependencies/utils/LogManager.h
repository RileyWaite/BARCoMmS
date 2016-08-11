#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "isat/utils/String.h"
#include "isat/utils/Log.h"

namespace isat_utils
{

class LogManager
{
   public:

      static LogManager& getInstance();

      bool addLog(String logName, Log* log);

      Log* getDefaultLog();
      
      Log* getLog(String logName);
      

      
   protected:

      LogManager();
      ~LogManager();

      Log *defaultLog;
};

} // namespace isat_utils

#endif // LOGMANAGER_H
