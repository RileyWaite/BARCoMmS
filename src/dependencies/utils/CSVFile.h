#ifndef CSVFILE_H
#define CSVFILE_H

#include <fstream>
#include "../dependencies/utils/String.h"
#include "../dependencies/utils/ArrayList.h"

using namespace std;


namespace isat_utils
{


/**
 * Simple asbstraction to read and parse a comma separated value (CSV) file.
 *
 * CSVFile infile;
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
class CSVFile
{
   public:

      CSVFile();
      ~CSVFile();

      bool open(String filename);

      /**
       * Reads the next line in the file and makes it available to be parsed by the get*() methods.
       * @return false if no lines are left to read.
       */
      bool getLine();
      
      int getInt(int column, int defaultValue);
      double getDouble(int column, double defaultValue);
      bool getBool(int column, bool defaultValue);
      
      bool close();

   private:

      ifstream infile;
      ArrayList<String> fields;
};

}

#endif  // CSVFILE_H
