
#include <algorithm>
#include <new>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>
#include <ctype.h>
#include "../dependencies/utils/ArrayList.h"
#include "../dependencies/utils/String.h"

using namespace std;

namespace isat_utils
{
   
void
String::grow(int deltaSize)
{
   // Grow the current data buffer by the requested increment.
   
   int newsize = bufcapacity + deltaSize;
   
   char* tmpdata = new (std::nothrow) char[newsize];
   if (tmpdata == 0)
   {
      errflag = true;
      return;
   }

   // If the current buffer has stuff in it, copy that to the new buffer
   // and delete the current one. 
   if (data != 0)
   {
      memcpy(tmpdata, data, buflength);
      delete [] data;
   }

   // replace the current buffer with the new one.
   data = tmpdata;
   
   bufcapacity = newsize;
}


String::String()
{
   data = 0;
   buflength = 0;
   bufcapacity = 0;
   errflag = false;

   grow(1);
   data[0] = '\0';
   buflength = 1;
}


String::String(char const * charstr)
{
   data = 0;
   buflength = 0;
   bufcapacity = 0;
   errflag = false;
   
   if (error())
      return;  // XXX: Also log this somewhere so we know it happened.

   if (charstr == 0)
   {
      grow(1);
      data[0] = '\0';
      buflength = 1;
   }
   else
   {
      grow(strlen(charstr) + 1);
      strcpy(data, charstr);
      buflength = strlen(charstr) + 1;
   }
}


String::~String()
{
   if (data != 0)
   {
      delete [] data;
      buflength = 0;
   }
}

   
String::String(String const& rhs)
{
   data = 0;
   buflength = 0;
   bufcapacity = 0;
   errflag = false;

   grow(rhs.buflength);

   if (error())
      return;

   memcpy(data, rhs.data, rhs.buflength);   // Fix this.. won't work without null termination. strncpy()
   
   buflength = rhs.buflength;
}


String&
String::operator=(String rhs)
{
   swap(rhs);
   
   return *this;
}

   
String&
String::operator+=(String rhs)
{
   int freespace = bufcapacity - buflength + 1;   
   if (freespace <= rhs.buflength)
   {
      grow(rhs.buflength + 1);  // Might be bit much... better heuristic? (50%ish?)
   }

   strcat(data, rhs.data);

   buflength = buflength + rhs.buflength - 1;

   return *this;
}


bool
String::operator==(String rhs)
{
   if (buflength != rhs.buflength)
      return false;

   return strncmp(data, rhs.data, buflength) == 0;
}

bool
String::operator!=(String rhs)
{
   if (buflength != rhs.buflength)
      return true;

   return strncmp(data, rhs.data, buflength) != 0;
}

bool
String::operator<(String rhs)
{
   return strcmp(data, rhs.data) < 0;
}


bool
String::operator>(String rhs)
{
   return strcmp(data, rhs.data) > 0;
}

bool 
String::error() const
{
   return errflag;
}

int
String::length() const
{
   if (buflength == 0)
      return 0;

   if ((buflength == 1) && (data[0] == '\0'))
      return 0;
   
   return buflength - 1;
}


int
String::capacity() const
{
   return bufcapacity;
}

void
String::clear()
{
   if (errflag)
      return;
   
   buflength = 1;
   data[0] = '\0';
}

char const*
String::c_str() const
{
   if (errflag)
      return 0;

   return data;
}

bool
String::charAt(int index, char& c)
{
   if ((buflength == 0) || (index >= buflength))
      return false;

   c = data[index];

   return true;
}


String
String::substring(int startpos, int length)
{
   String result;
   
   if ((buflength == 0) || (startpos >= buflength))
      return result;

   if ((startpos + (length - 1)) >= buflength)
      return result;

   char tmpbuf[length+1];
   strncpy(tmpbuf, &(data[startpos]), length);
   tmpbuf[length]='\0';

   result = String(tmpbuf);
   
   return result;
}

String
String::toLower() const
{
   String tmp(*this);

   for (int i = 0; i < tmp.buflength; i++)
      tmp.data[i] = tolower(tmp.data[i]);

   return tmp;
}


String
String::toUpper() const
{
   String tmp(*this);

   for (int i = 0; i < tmp.buflength; i++)
      tmp.data[i] = toupper(tmp.data[i]);

   return tmp;   
}


String
String::format(String formatString, int val)
{
   char buf[1024];
   int len = snprintf(buf, 1024, formatString.c_str(), val);

   return String(buf);
}

String
String::format(String formatString, float val)
{
   char buf[1024];
   int len = snprintf(buf, 1024, formatString.c_str(), val);

   return String(buf);
}

String
String::format(String formatString, double val)
{
   char buf[1024];
   int len = snprintf(buf, 1024, formatString.c_str(), val);

   return String(buf);   
}   

bool
String::parseInt(long& value)
{
   char *endptr = 0;
   value = strtol(c_str(), &endptr, 0);
   
   if (*endptr != '\0')
      return false;
   
   return true;
}

bool
String::parseDouble(double& value)
{
   char *endptr = 0;
   value = strtod(c_str(), &endptr);

   if (endptr == c_str())
      return false;

   return true;
}

bool
String::parseBool(bool& value)
{
   if (buflength == 0)
   {
      value = false;
      return true;
   }

   if ((data[0] == 't') ||
       (data[0] == 'T') ||
       (data[0] == 'Y') ||
       (data[0] == '1'))
   {
      value = true;
      return true;
   }

   value = false;
   
   return true;
}


bool
String::parseHex(long& value)
{
   char *endptr = 0;
   value = strtoul(c_str(), &endptr, 0);
   
   if (*endptr != '\0')
      return false;
   
   return true;
}

bool
String::matches(String regex) const
{
   bool result = false;
   
   regex_t compiled_re;
   if (regcomp(&compiled_re, regex.c_str(), REG_NOSUB) == 0)
   {
      result = (regexec(&compiled_re, data, 0, 0, 0) == 0);
   }
   regfree(&compiled_re);
   
   return result;
}


ArrayList<String>
String::split(String regex) const
{
   ArrayList<String> results;
   
   regex_t compiled_re;
   if (!(regcomp(&compiled_re, regex.c_str(), REG_EXTENDED) == 0))
      return results;
   
   regmatch_t matches[10];
   int startpos = 0;
   while (regexec(&compiled_re, &(data[startpos]), 10, matches, 0) == 0)
   {
      if (matches[0].rm_so == -1)
         break;
         
      cout << startpos + matches[0].rm_so << ", " << startpos + matches[0].rm_eo << endl;
      startpos = startpos + matches[0].rm_eo + 1;
   }
   regfree(&compiled_re);
   
   return results;
}

void
String::swap(String& a)
{
   std::swap(data, a.data);
   std::swap(buflength, a.buflength);
   std::swap(bufcapacity, a.bufcapacity);
   std::swap(errflag, a.errflag);
}
   
// friend functions
ostream&
operator<<(ostream& ostr, String const& str)
{
   ostr << str.data;
   
   return ostr;
}

String
operator+(String a, String b)
{
   String tmp(a);
   tmp += b;

   return tmp;
}


}  // namespace isat_utils


