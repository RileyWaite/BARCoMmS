#include <stdlib.h>
#include <iostream>
#include "isat/utils/GNCDataFile.h"
#include "isat/utils/String.h"
#include "isat/utils/System.h"

using namespace std;
using namespace isat_utils;


int
main(int argc, char** argv)
{

   String datafilename = "archive/gnc/milIn.dat";
   cout << "Reading '" << datafilename << "'\n";

   GNCDataFile dfile;
   if (!dfile.open(datafilename))
   {
      cout << "Problem opening file.\n";
      exit(1);
   }

   int line = 0;
   while (dfile.getLine())
   {
      cout << "line: " << line++ << endl;
      for (int i = 0; i < 69; i++)
      {
         cout << i << ": " << dfile.getDouble(i) << endl;
      }
   }
}
