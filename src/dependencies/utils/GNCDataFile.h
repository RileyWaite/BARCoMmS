#ifndef GNCDATAFILE_H
#define GNCDATAFILE_H

#include <stdio.h>
#include "../dependencies/utils/String.h"
#include "../dependencies/utils/ArrayList.h"

using namespace std;


namespace isat_utils
{


/**
 * Simple asbstraction to read and parse a comma separated value (CSV) file.
 *
 * GNCDataFile infile;
 * infile.open("foo.csv");
 *
 * while(infile.getLine())
 * {
 *    int param1 = infile.getInt(26, 0); // Read column 26 as int, default value 0
 *    double param2 = infile.getDouble(14, 3.14); // Read column 14 as double, default value 3.14.
 * }
 * 
 * infile.close();
 *
 */
class GNCDataFile
{
   public:

      GNCDataFile();
      ~GNCDataFile();

      bool open(String filename);

      /**
       * Reads the next line in the file and makes it available to be parsed by the get*() methods.
       * @return false if no lines are left to read.
       */
      bool getLine();
      
      double getDouble(int column);
      
      bool close();

   private:

      FILE* infile;
      static const int num_fields = 68;
      double fields[68];
};

}

#endif  // GNCDATAFILE_H
