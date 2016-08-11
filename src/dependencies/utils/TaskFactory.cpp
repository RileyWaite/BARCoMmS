
#include <dlfcn.h>
#include "isat/utils/TaskFactory.h"
#include "isat/utils/LogManager.h"
#include "isat/utils/Log.h"


namespace isat_utils
{

TaskFactory::TaskFactory(File pluginDirectoryPath)
   : pluginDir(pluginDirectoryPath),
     logger("TaskFactory")
{
   logger.setLog(LogManager::getInstance().getDefaultLog());

   if (!(pluginDir.exists() && pluginDir.isDirectory()))
      logger.error("Problem with plugin directory '" + std::string(pluginDir.getName().c_str()) + "'");
}

ISATTask*
TaskFactory::createTask(String taskName, String pluginName)
{

   File pluginFile = File(pluginDir.getName() + "/" + pluginName);
   if (!pluginFile.exists())
   {
      logger.warn("Requested plugin '" + std::string(pluginName.c_str()) + "' not found");
      return 0;
   }
   
   void *libraryHandle = dlopen(pluginFile.getName().c_str(), RTLD_NOW);

   if (libraryHandle == 0)
   {
      logger.warn("Unable to load plugin '" + std::string(pluginName.c_str()) + "'");
      logger.warn(dlerror());
      return 0;
   }



   void* gptr = dlsym(libraryHandle, "createTask");
   if (gptr == 0)
   {
      logger.warn("Couldn't find createTask function in plugin '" + std::string(pluginName.c_str()) + "'");
      return 0;
   }

   typedef ISATTask* (*CreateTaskPtr)(char const*);   
   CreateTaskPtr createTask = reinterpret_cast<CreateTaskPtr>(reinterpret_cast<long>(gptr));

   return createTask(taskName.c_str());
}

}
