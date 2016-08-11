#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "isat/utils/String.h"
#include "isat/utils/System.h"
#include "isat/utils/Timer.h"


using namespace std;
using namespace isat_utils;


int
main(int argc, char** argv)
{
   cout << "ISAT_ROOT = '" << System::getEnv("ISAT_ROOT") << "'\n";
   cout << "FOO = '" << System::getEnv("FOO") << "'\n";

   String result = String(System::getEnv("FOO").c_str());
   if (result == "")
      cout << "Foo was null.\n";

   Timer timer;
   timer.start();

   for (int i = 0; i < 5; i++)
   {
      cout << System::getTimeInMilliseconds() << endl;
      cout << "Elapsed time: " << timer.elapsedTimeInMillis() << endl;
      sleep(1);
   }


}

