#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <stdint.h>

namespace isat_utils
{

   /**
    * A buffer of bytes with useful get/set methods.
    *
    * Modelled after Java's class of the same name. This class wraps a
    * buffer of bytes and provides get and set methods for various
    * types commonly found in network packets. The byte order can be
    * switch back and forth, even between gets (some packet formats
    * have both big and little endian byte orders. Annoying.)
    *
    * The abstraction is a buffer with a maximum size and a current
    * read/write pointer. Reading or writing advances the pointer by
    * the size of whatever was read.
    */
class ByteBuffer
{
   public:

      enum ByteOrder { LittleEndian, BigEndian };

      /**
       * Create a ByteBuffer capable of holding up to maxsize bytes.
       */
      ByteBuffer(int maxSize = 100);
      ByteBuffer(ByteBuffer const& rhs);
      ByteBuffer& operator=(ByteBuffer rhs);
      ~ByteBuffer();

      /**
       * Clears the buffer by resetting the read/write pointer to zero. identical to seek(0).
       */
      void clear();

      /**
       * Move the read/write pointer to pos.
       */
      bool seek(int pos);

      /**
       * @return The current offset of the read/write pointer.
       */
      int getPosition() const;

      int getLimit() const;

      int getCapacity() const;
      
      /**
       * Return a pointer to the raw bytes in this instance.
       */
      char const* getBytes() const;

      void setByteOrder(ByteOrder order);

      ByteOrder getByteOrder();

      ByteOrder getNativeByteOrder();


      /**
       * Write count zero bytes into buffer at current location.
       */
      bool zero(int count);
      
      /**
       * Write length bytes from data into this instance's buffer.
       */
      bool put(char const* data, int length);

      bool putByte(unsigned char val);
      
      bool putBoolean(bool val);

      bool putShort(short val);
      
      bool putInt(int val);

      bool putFloat(float val);

      bool putDouble(double val);

      bool putInt32(int32_t val);
      bool putInt64(int64_t val);
      bool putUint32(uint32_t val);
      bool putUint64(uint64_t val);


      //bool get(char*& data, int length);

      bool getByte(unsigned char& val);
      
      bool getBoolean(bool& value);

      bool getShort(short& value);
      
      bool getInt(int& value);


      bool getFloat(float& value);

      bool getDouble(double& value);
      
      bool getInt32(int32_t& value);
      bool getInt64(int64_t& value);
      bool getUint32(uint32_t& value);
      bool getUint64(uint64_t& value);


      // The following methods allow direct access to bit fields within the byte buffer.
      // There is no concept of a position or a seek, the bit offset and field size is
      // specified in the call to the method.

      bool getBits(int bitOffset, int bitWidth, int& value);

      bool putBits(int bitOffset, int bitWidth, int value);
      
   protected:

      char* buffer;
      int maxSize;
      int pos;
      int limit;
      
      ByteOrder byteOrder;
      ByteOrder nativeByteOrder;

      void swapInstance(ByteBuffer& rhs);
};

}  // namespace isat_utils


#endif // BYTEBUFFER_H
