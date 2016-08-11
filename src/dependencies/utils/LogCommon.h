#ifndef LOGCOMMON_H
#define LOGCOMMON_H

namespace isat_utils
{

class LogCommon
{
   public:

      enum LogLevel { ALL   = 0,
                      DEBUG = 1,
                      INFO  = 2,
                      WARN  = 4,
                      ERROR = 8,
                      FATAL = 16,
                      OFF   = 32
      };
};

} // namespace isat_utils

#endif // LOGCOMMON_H
