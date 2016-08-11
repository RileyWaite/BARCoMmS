#include "isat/utils/CSVFile.h"

namespace isat_utils
{

CSVFile::CSVFile()
{
}

CSVFile::~CSVFile()
{
}


bool
CSVFile::open(String filename)
{
   infile.open(filename.c_str());

   return !infile.fail();
}

bool
CSVFile::getLine()
{
   if (infile.eof())
      return false;

   char buf[1000];
   infile.getline(buf, 1000);
   if (infile.fail())
      return false;

   String lineBuf = String(buf);
   //   fields = 
   
   return true;
}

int
CSVFile::getInt(int column, int defaultValue)
{
   return false;
}

double
CSVFile::getDouble(int column, double defaultValue)
{
   return 0.0;
}

bool
CSVFile::getBool(int column, bool defaultValue)
{
   return false;
}

bool
CSVFile::close()
{
   return false;
}


}
