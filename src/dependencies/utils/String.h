#ifndef STRING_H
#define STRING_H

#include <iostream>
#include "../dependencies/utils/ArrayList.h"

using namespace std;


namespace isat_utils
{
   /**
    * This class provides a basic string class.
    *
    * We're not using STL or boost because of the ban on
    * exceptions. This class provides a string class which provides
    * modern string like behavior: Dynamic allocated memory, regular
    * expressions, operations on strings, conversion to and from
    * char*, etc. Not perfect, but better than chasing char* all over
    * the place.
    *
    * XXX: Modify this class to resize. File needs it and it's just dumb not to. --jamie
    */
   class String
   {
      public:

         /**
          * Default constructor.
          */
         String();

         /**
          * Construct a String instance and initialize from the
          * specified null terminated char* string.
          */
         String(char const * charstring);


         /**
          * Copy constructor.
          */
         String(String const& rhs);

         /**
          * Assignment operator.
          */
         String& operator=(String rhs);

         
         String& operator+=(String rhs);


         /**
          * Equality operator.
          */
         bool operator==(String rhs);

         bool operator!=(String rhs);
         
         bool operator<(String rhs);

         bool operator>(String rhs);


         
         /**
          * The length of a string is the number of characters (not
          * including the null terminator) currently stored in this
          * String instance.
          *
          * @return Number of characters currently stored (not including null terminator).
          */
         int length() const;


         /**
          * The capacity is the maximum number of characters that can be stored in this String instance.
          *
          * @return Capacity of this instance.
          */
         int capacity() const;


         /**
          * Resets length of this instance to zero.
          */
         void clear();


         /**
          * Access the null terminated 'C' string representation of this instance.
          *
          * @return A pointed to the null terminated C string encapsulated by this String instance.
          */
         char const* c_str() const;

         /**
          * Get the character at string position 'index'. Positions
          * start a zero (first character) through length -1.
          *
          * @return false if index is out of range.
          */
         bool charAt(int index, char& c);

         String substring(int startpos, int length);
         
         /**
          * Return a copy of the string converted to lower case.
          */
         String toLower() const;

         /**
          * Return a copy of the string converted to upper case.
          */
         String toUpper() const;


         static String format(String formatString, int val);
         static String format(String formatString, float val);
         static String format(String formatString, double val);
         

         bool parseInt(long& value);
         bool parseDouble(double& value);
         bool parseBool(bool& value);
         bool parseHex(long& value);
         
         /**
          * Determine if this instance matches the given POSIX regular expression.
          *
          * @return true if this instance matches the regex.
          */
         bool matches(String regex) const;

         ArrayList<String> split(String regex) const;
         
         friend ostream& operator<<(ostream& ostr, String const& str);

         friend String operator+(String a, String b);

         
         /**
          * Destructor.
          */
         ~String();


         /**
          * Determine if this instance is valid (no errors have occured).
          *
          * @return true if instance is valid (can be used).
          */
         bool error() const;
         
         
      private:


         char* data;
         int   buflength;   // Current length data in data buffer.
         int   bufcapacity; // Max length of data buffer.
         bool  errflag;

         void grow(int deltaSize);

         // Swap the contents of this string with string a.
         void swap(String& a);
         
   };
}  // namespace isat_utils


#endif // STRING_H
