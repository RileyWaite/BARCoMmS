#ifndef TASKFACTORY_H
#define TASKFACTORY_H

#include "isat/spriteext/ISATTask.h"
#include "isat/utils/String.h"
#include "isat/utils/File.h"
#include "isat/utils/Logger.h"


using namespace isat_spriteext;


namespace isat_utils
{

class TaskFactory
{
   public:

      /**
       * Create a task factory that can load and create tasks from
       * dynamic libraries located in the specified plugin directory.
       */
      TaskFactory(File pluginDirectoryPath);

      /**
       * Create a task with the given name using the "createTask" function in the specified plugin.
       *
       * @param taskName - the name given to the task instance created.
       * @param pluginName - The name of the dynamic library (.so) minus the ".so" part. Example "gps" refers to "gps.so".
       *
       */
      ISATTask* createTask(String taskName, String pluginName);

   protected:

      File pluginDir;
      Logger logger;
};

}

#endif  // TASKFACTORY_H
