
#include <iostream>
#include <iomanip>
#include "isat/utils/ByteBuffer.h"

using namespace isat_utils;
using namespace std;


ostream&
operator<<(ostream& ostr, ByteBuffer& buf)
{
   char const* data = buf.getBytes();

   int l = buf.getLimit();
   if (l > 0)
      cout << "|";
   for (int i = 0; i < l; i++)
   {
      char curByte = data[i];
      for (int j = 7; j >= 0; j--)
      {
         int curBit = (curByte & (0x1 << j)) >> j;
         if (curBit)
            cout << "1";
         else
            cout << "0";
         if (j == 4)
            cout << " ";
      }
      cout << "|";
   }

   
   return ostr;
}
                                        

int
main(int argc, char** argv)
{
   ByteBuffer buf(100);

   std::cout << "Native byte order: "
             << ((buf.getNativeByteOrder() == ByteBuffer::LittleEndian) ? "Little Endian" : "Big Endian") << std::endl;



   buf.setByteOrder(ByteBuffer::BigEndian);
   buf.clear();
   buf.putInt(100);
   buf.putInt(42);
   buf.setByteOrder(ByteBuffer::LittleEndian);
   buf.putBoolean(true);
   buf.putFloat(2.718);
   buf.putDouble(3.141592654);

   int intval;
   bool boolval;
   float floatval;
   double doubleval;
   
   buf.seek(0);
   buf.setByteOrder(ByteBuffer::BigEndian);
   
   buf.getInt(intval);
   std::cout << "Should be 100:         " << intval << std::endl;

   buf.getInt(intval);
   std::cout << "Should be 42:          " << intval << std::endl;
   
   buf.setByteOrder(ByteBuffer::LittleEndian);
   buf.getBoolean(boolval);
   std::cout << "Should be true:        " << boolval << std::endl;

   buf.getFloat(floatval);
   std::cout << "Should be 2.718:       " << floatval << std::endl;

   buf.getDouble(doubleval);
   std::cout << "Should be 3.141592654: " << std::setprecision(10) << doubleval << std::endl;

   std::cout << "\nSeeking to 2nd value:" << std::endl;
   buf.seek(4);
   buf.setByteOrder(ByteBuffer::BigEndian);

   buf.getInt(intval);
   std::cout << "Should be 42:          " << intval << std::endl;

   std::cout << "current position (should be 8): " << buf.getPosition() << std::endl;

   
}
