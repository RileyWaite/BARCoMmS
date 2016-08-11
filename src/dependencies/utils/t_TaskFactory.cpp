
#include "isat/utils/TaskFactory.h"
#include "isat/utils/File.h"

int
main(int argc, char** argv)
{
   TaskFactory tf(File("lib/plugins"));

   ISATTask *it = tf.createTask("TestTask", "TestPlugin.so");

   if (it != 0)
      it->execute();
}
