#include "isat/utils/GNCDataFile.h"

namespace isat_utils
{

GNCDataFile::GNCDataFile()
{
}

GNCDataFile::~GNCDataFile()
{
}


bool
GNCDataFile::open(String filename)
{
   infile = fopen(filename.c_str(), "r");
   if (!infile)
      return false;

   return true;
}

bool
GNCDataFile::getLine()
{
   if (feof(infile))
      return false;

   for (int i = 0; i < num_fields; i++)
   {
      fscanf(infile, "%lf", &(fields[i]));
   }
   
   return true;
}

double
GNCDataFile::getDouble(int column)
{
   return fields[column];
}


bool
GNCDataFile::close()
{
   fclose(infile);
   return true;
}


}
