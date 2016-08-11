
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include "ByteBuffer.h"

using namespace std;

namespace isat_utils
{

static void
swap1(char* a, char* b)
{
   char tmp = *a;
   *a = *b;
   *b = tmp;
}

static void
swap2(char* val)
{
   swap1(&(val[0]), &(val[1]));
}

static void
swap4(char* val)
{
   swap1(&(val[0]), &(val[3]));
   swap1(&(val[1]), &(val[2]));
}

static void
swap8(char* val)
{
   swap1(&(val[0]), &(val[7]));
   swap1(&(val[1]), &(val[6]));
   swap1(&(val[2]), &(val[5]));
   swap1(&(val[3]), &(val[4]));
}


ByteBuffer::ByteBuffer(int maxSize)
   :buffer(0),
    pos(0),
    limit(0)
{
   this->maxSize = maxSize;
   buffer = (char*) malloc(this->maxSize);

   // Determine the byte order of the machine we're running on.
   if (htonl(0x01234567) == 0x01234567)
      nativeByteOrder = BigEndian;
   else
      nativeByteOrder = LittleEndian;

   byteOrder = nativeByteOrder;
}


ByteBuffer::ByteBuffer(ByteBuffer const& rhs)
{
   this->maxSize = rhs.maxSize;
   buffer = (char*) malloc(this->maxSize);
   memcpy(buffer, rhs.buffer, rhs.pos);

   nativeByteOrder = rhs.nativeByteOrder;
   byteOrder = rhs.byteOrder;

   pos = rhs.pos;
   limit = rhs.limit;
}


ByteBuffer&
ByteBuffer::operator=(ByteBuffer rhs)
{
   swapInstance(rhs);
   return *this;
}

ByteBuffer::~ByteBuffer()
{
   if (buffer != 0)
      free(buffer);

   buffer = 0;
}

void
ByteBuffer::swapInstance(ByteBuffer& rhs)
{
   std::swap(buffer, rhs.buffer);
   std::swap(maxSize, rhs.maxSize);
   std::swap(pos, rhs.pos);
   std::swap(limit, rhs.limit);
   std::swap(byteOrder, rhs.byteOrder);
   std::swap(nativeByteOrder, rhs.nativeByteOrder);
}
   
void
ByteBuffer::clear()
{
   pos = 0;
   limit = 0;
}


bool
ByteBuffer::seek(int p)
{
   if (p > maxSize)
      return false;
   
   pos = p;

   return true;
}


int
ByteBuffer::getPosition() const
{
   return pos;
}

int
ByteBuffer::getLimit() const
{
   return limit;
}
   
int
ByteBuffer::getCapacity() const
{
   return maxSize;
}


char const*
ByteBuffer::getBytes() const
{
   return buffer;
}


void
ByteBuffer::setByteOrder(ByteOrder order)
{
   byteOrder = order;
}


ByteBuffer::ByteOrder
ByteBuffer::getByteOrder()
{
   return byteOrder;
}


ByteBuffer::ByteOrder
ByteBuffer::getNativeByteOrder()
{
   return nativeByteOrder;
}


bool
ByteBuffer::zero(int count)
{
   bool result = true;
   int bytesToZero = count;
   if (bytesToZero > (maxSize - pos))
   {
      bytesToZero = maxSize - pos;
      result = false;
   }

   memset(&(buffer[pos]), 0x0, bytesToZero);
   pos = pos + bytesToZero;

   if (pos > limit)
      limit = pos;

   return result;
}


bool
ByteBuffer::put(char const* data, int length)
{
   bool result = true;
   
   int bytesToCopy = length;
   if (bytesToCopy > (maxSize - pos))
   {
      bytesToCopy = maxSize - pos;
      result = false; // some or all of the bytes failed to copy.
   }

   memcpy(&(buffer[pos]), data, bytesToCopy);
   pos = pos + bytesToCopy;

   if (pos > limit)
      limit = pos;
   
   return result;
}


bool
ByteBuffer::putByte(unsigned char val)
{
   if (pos > (maxSize - 1))
      return false;

   buffer[pos] = val;
   pos = pos + 1;

   if (pos > limit)
      limit = pos;
   
   return true;
}


bool
ByteBuffer::putBoolean(bool val)
{
   if (pos < (maxSize - 1))
   {
      buffer[pos++] = val;

      if (pos > limit)
         limit = pos;
      
      return true;
   }

   return false;
}


bool
ByteBuffer::putShort(short val)
{
   if (pos > int(maxSize - sizeof(short)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap2((char*)&val);
   
   memcpy(&(buffer[pos]), &val, sizeof(short));
   pos = pos + sizeof(short);

   if (pos > limit)
      limit = pos;
   
   return true;
}


bool
ByteBuffer::putInt(int val)
{
   if (pos > int(maxSize - sizeof(int)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);
   
   memcpy(&(buffer[pos]), &val, sizeof(int));
   pos = pos + sizeof(int);

   if (pos > limit)
      limit = pos;
   
   return true;
}



bool
ByteBuffer::putFloat(float val)
{
   if (pos > int(maxSize - sizeof(float)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);

   memcpy(&(buffer[pos]), &val, sizeof(float));
   pos = pos + sizeof(float);

   if (pos > limit)
      limit = pos;
   
   return true;
}


bool
ByteBuffer::putDouble(double val)
{
   if (pos > int(maxSize - sizeof(double)))
      return false;
   
   if (byteOrder != nativeByteOrder)
      swap8((char*)&val);

   memcpy(&(buffer[pos]), &val, sizeof(double));
   pos = pos + sizeof(double);

   if (pos > limit)
      limit = pos;
   
   return true;
}

bool
ByteBuffer::putInt32(int32_t val)
{
   if (pos > int(maxSize - sizeof(int32_t)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);

   memcpy(&(buffer[pos]), &val, sizeof(int32_t));
   pos = pos + sizeof(int32_t);

   if (pos > limit)
      limit = pos;

   return true;
}

bool
ByteBuffer::putUint32(uint32_t val)
{
   if (pos > int(maxSize - sizeof(uint32_t)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);

   memcpy(&(buffer[pos]), &val, sizeof(uint32_t));
   pos = pos + sizeof(uint32_t);

   if (pos > limit)
      limit = pos;

   return true;
}


bool
ByteBuffer::putInt64(int64_t val)
{
   if (pos > int(maxSize - sizeof(int64_t)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap8((char*)&val);
   
   memcpy(&(buffer[pos]), &val, sizeof(int64_t));
   pos = pos + sizeof(int64_t);

   if (pos > limit)
      limit = pos;
   
   return true;
}


bool
ByteBuffer::putUint64(uint64_t val)
{
   if (pos > int(maxSize - sizeof(uint64_t)))
      return false;

   if (byteOrder != nativeByteOrder)
      swap8((char*)&val);
   
   memcpy(&(buffer[pos]), &val, sizeof(uint64_t));
   pos = pos + sizeof(uint64_t);

   if (pos > limit)
      limit = pos;
   
   return true;
}



#if 0
void
ByteBuffer::get(void* data, int length)
{

}
#endif

bool
ByteBuffer::getByte(unsigned char& val)
{
   if (pos > int(maxSize - sizeof(unsigned char)))
      return false;

   val = buffer[pos];
   pos = pos + sizeof(unsigned char);

   return true;
}
   
bool
ByteBuffer::getBoolean(bool& val)
{
   val = false;
   
   if (pos < int(maxSize - sizeof(bool)))
   {
      val = buffer[pos++];
      return true;
   }

   return false;
}


bool
ByteBuffer::getShort(short& val)
{
   if (pos > int(maxSize - sizeof(short)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(short));
   pos = pos + sizeof(short);

   if (byteOrder != nativeByteOrder)
      swap2((char*)&val);
   
   return true;
}


bool
ByteBuffer::getInt(int& val)
{
   if (pos > int(maxSize - sizeof(int)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(int));
   pos = pos + sizeof(int);

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);
   
   return true;
}

bool
ByteBuffer::getInt32(int32_t& val)
{
   if (pos > int(maxSize - sizeof(int32_t)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(int32_t));
   pos = pos + sizeof(int32_t);

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);
   
   return true;
}


bool
ByteBuffer::getUint32(uint32_t& val)
{
   if (pos > int(maxSize - sizeof(uint32_t)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(uint32_t));
   pos = pos + sizeof(uint32_t);

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);
   
   return true;
}


bool
ByteBuffer::getUint64(uint64_t& val)
{
   if (pos > int(maxSize - sizeof(uint64_t)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(uint64_t));
   pos = pos + sizeof(uint64_t);

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);
   
   return true;
}


bool
ByteBuffer::getFloat(float& val)
{

   if (pos > int(maxSize - sizeof(float)))
      return false;

   val = 0.0;
   memcpy(&val, &(buffer[pos]), sizeof(float));
   pos = pos + sizeof(float);

   if (byteOrder != nativeByteOrder)
      swap4((char*)&val);

   return true;
}


bool
ByteBuffer::getDouble(double& val)
{
   if (pos > int(maxSize - sizeof(double)))
      return false;
   
   val = 0.0;
   memcpy(&val, &(buffer[pos]), sizeof(double));
   pos = pos + sizeof(double);

   if (byteOrder != nativeByteOrder)
      swap8((char*)&val);
   
   return true;
}

bool
ByteBuffer::getInt64(int64_t& val)
{
   if (pos > int(maxSize - sizeof(int64_t)))
      return false;
   
   val = 0;
   memcpy(&val, &(buffer[pos]), sizeof(int64_t));
   pos = pos + sizeof(int64_t);

   if (byteOrder != nativeByteOrder)
      swap8((char*)&val);
   
   return true;
}



bool
ByteBuffer::getBits(int bitOffset, int bitWidth, int& value)
{
   // XXX: Fix this. Remove bitfield size limitation.
   if (bitWidth > 56)
   {
      printf("ByteBuffer::getBits  bitfield too big! (bitWidth = %d)\n", bitWidth);
      return false;
   }
   
   // Which bytes contain the bits we want?
   int startByte = bitOffset / 8;
   if ((startByte < 0) || (startByte >= limit))
      return false;
   
   int endByte = (bitOffset + bitWidth - 1) / 8;
   if ((endByte < 0) || (endByte >= limit))
      return false;

   // Put those bytes into a register (well, probably not really, but
   // putting them in a variable makes it easier to perform bit
   // operations on all of the bytes at the same time.
   long long bitbuf = 0;
   for (int i = startByte; i <= endByte; i++)
   {
      bitbuf = bitbuf << 8;
      bitbuf = bitbuf | (unsigned char) buffer[i];
   }

   // Move the bitfield we're trying to read to the extreme right
   // and chop off the unwanted part to the left. What remains is
   // the value we're after.
   bitbuf = bitbuf >> (7 - ((bitOffset + bitWidth - 1) % 8));
   bitbuf = bitbuf & ((1LL << bitWidth) - 1);

   value = bitbuf;
   
   return true;
}

bool
ByteBuffer::putBits(int bitOffset, int bitWidth, int value)
{
   // XXX: Fix this. Remove bitfield size limitation.
   if (bitWidth > 56)
   {
      printf("ByteBuffer::putBits  bitfield too big! (bitWidth = %d)\n", bitWidth);
      return false;
   }

   
   // Can the value fit in the destination bitfield?
   if (((unsigned int) value) > ((1LL << bitWidth) - 1))
   {
      printf("value too large in putBits. value = %d, field width = %d\n", value, bitWidth);
      return false;
   }
   
   // Which bytes contain the bits we want?
   int startByte = bitOffset / 8;
   if ((startByte < 0) || (startByte >= limit))
      return false;
   
   int endByte = (bitOffset + bitWidth - 1) / 8;
   if ((endByte < 0) || (endByte >= limit))
      return false;   

   // Put those bytes into a register (well, probably not really, but
   // putting them in a variable makes it easier to perform bit
   // operations on all of the bytes at the same time.   
   long long bitbuf = 0;
   for (int i = startByte; i <= endByte; i++)
   {
      bitbuf = bitbuf << 8;
      bitbuf = bitbuf | (unsigned char) buffer[i];
   }


   // Create a write mask that will be used to zero the bits in the
   // destination bitfield. Shift it left so it lines up with the
   // bitfield we're overwriting, and then negate it so we end up
   // with zeros at the bitfield locations and 1's everywhere else.
   // After and'ing with bitbuf, the bits in the destination bitfield are
   // all zero. 
   long long writeMask = (1LL << bitWidth) - 1;
   writeMask = writeMask << 7 - ((bitOffset + bitWidth - 1) % 8);
   writeMask = ~writeMask;

   bitbuf = bitbuf & writeMask;

   // Shift the value to write to the left until it lines up with the
   // bitfield in bifbut. 
   long long valbuf = value << (7 - ((bitOffset + bitWidth - 1) % 8));

   // "or" the value with bitbuf, writing it to the bitfield.
   bitbuf = bitbuf | valbuf;

   // Write the modified bytes back to the ByteBuffer's buffer.
   for (int i = endByte; i >= startByte; i--)
   {
      buffer[i] = bitbuf & 0xff;
      bitbuf = bitbuf >> 8;
   }

   return true;
}
   
}  // namespace isat_utils
