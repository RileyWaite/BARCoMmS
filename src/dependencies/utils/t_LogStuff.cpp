
#include "isat/utils/LogManager.h"
#include "isat/utils/Logger.h"
#include "isat/utils/Log.h"
#include "isat/utils/ColorLogFormatter.h"

using namespace isat_utils;

int
main(int argc, char** argv)
{
   LogManager& lm = LogManager::getInstance();

   Log* log = lm.getDefaultLog();
   Logger logger("GPS");
   logger.setLog(log);

   logger.debug("This is a debug message.");
   logger.info("And here's an info entry.");
   logger.warn("warning, will robinson!");
   logger.error("You got your error in my message.");
   logger.fatal("I'm... hit. Going down....");
}
