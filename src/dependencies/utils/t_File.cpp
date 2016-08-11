
#include <iostream>
#include <stdlib.h>
#include "isat/utils/File.h"

using namespace std;
using namespace isat_utils;

int
main(int argc, char** argv)
{
   if (argc != 2)
   {
      cout << "Usage: t_File <pathname>\n";
      exit(0);
   }
   
   File file(argv[1]);

   if (file.exists())
      cout << "It's there.\n";

   ArrayList<String> entries = file.list();
   for (int i = 0; i < entries.size(); i++)
   {
      String entry;
      entries.get(i, entry);
      File f(file.getName() + "/" + entry);      

      cout << "File: '" << f.getName() << "'";
      

      if (f.isFile())
         cout << "   size: " << f.length();

      cout << "   atime: " << f.lastAccessTime();
      cout << "   mtime: " << f.lastDataModificationTime();
      
      cout << "\n";
   }
   
}
