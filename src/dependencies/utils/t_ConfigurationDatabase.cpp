
#include <iostream>
#include "isat/utils/ConfigurationDatabase.h"

using namespace std;
using namespace isat_utils;

int
main(int argc, char** argv)
{
   ConfigurationDatabase& cd = ConfigurationDatabase::getInstance();

   cd.load(File("resources/fsw/config"));

   ArrayList<String> params = cd.getParamNames();

   cout << "Parameters in database:\n";
   for (int i = 0; i < params.size(); i++)
   {
      String name;
      params.get(i, name);

      cout << "   '" << name << "'\n";
   }
   
   
   
   cout << "\nioboard.magtorquer.y.max: " << (int) cd.getInt("ioboard.magtorquer.y.max", 0) << "\n";
   cout << "\njamie.bar: " << (int) cd.getInt("jamie.bar", 0) << endl;

}
