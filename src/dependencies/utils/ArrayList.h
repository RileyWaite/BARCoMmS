#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <new>

using namespace std;


namespace isat_utils
{

/**
 * Exception safe version of a simple list container. Modeled after java's ArrayList.
 *
 * Unlike std::vector, An ArrayList instance's size is fixed when
 * created. The number of elements in the list may change (the 'size') but the
 * capacity never changes.
 *
 * Note that because it's "exception safe" (throws no exceptions),
 * certain compromises in ease of use had to be made. Often, the
 * natural way to do a particular thing (return a value) leaves no
 * room for an error code (other than an exception). If the interface
 * seems awkward in places, this is why.
 */


   
template <class T>
class ArrayList
{
   public:

      ArrayList(int maxSize = 100);
      ArrayList(ArrayList<T> const& rhs);
      ArrayList<T>& operator=(ArrayList<T>& rhs);
      ~ArrayList<T>();

      bool error();

      void clear();
      bool add(T element);
      /**
       * Insert element in 
       */
      bool put(int index, T element);
      bool contains(T element);
      bool get(int index, T& element) const;
      bool indexOf(T element, int& index) const;
      bool isEmpty();
      bool remove(int index);
      bool removeElement(T element);
      bool set(int index, T element);
      int size() const;
      int capacity() const;
      
      
   private:

      char* data;
      int dataSize;      // Current number of elements in data.
      int dataCapacity;  // Maximum number of elements permitted in data.
      bool errflag;

      void init(int maxSize);

};


template <class T>
void
ArrayList<T>::init(int maxSize)
{
   data = 0;
   dataSize = 0;
   dataCapacity = 0;
   errflag = 0;

   // Try to allocate a data buffer of the requested size.

   data = new (std::nothrow) char[sizeof(T) * maxSize];
   if (data == 0)
   {
      errflag = true;
      return;
   }

   dataCapacity = maxSize;

   
   // Fill it up with instances using the default constructor of T.
   for (int i = 0; i < dataCapacity; i++)
   {
      new (&data[i * sizeof(T)]) T;
   }      
}


template <class T>
ArrayList<T>::ArrayList(int maxSize)
{
   init(maxSize);
}


template <class T>
ArrayList<T>::ArrayList(ArrayList<T> const& rhs)
{
   // Create a data buffer just big enough to hold rhs.
   init(rhs.size());

   if (error())
      return;  // XXX: Also log this somewhere so we know it's happening.

   // Copy the elements in rhs into the new instance.
   for (int i = 0; i < rhs.dataSize; i++)
   {
      T* a = reinterpret_cast<T*>(&data[i * sizeof(T)]);
      T* b = reinterpret_cast<T*>(&rhs.data[i * sizeof(T)]);

      *a = *b;
   }
   
   dataSize = rhs.dataSize;
}


template <class T>
ArrayList<T>&
ArrayList<T>::operator=(ArrayList<T>& rhs)
{
   int amountToCopy = rhs.dataSize;
   if (amountToCopy > dataCapacity)
      amountToCopy = dataCapacity;

   // Copy the elements in rhs into this instance.
   for (int i = 0; i < amountToCopy; i++)
   {
      T* a = reinterpret_cast<T*>(&data[i * sizeof(T)]);
      T* b = reinterpret_cast<T*>(&rhs.data[i * sizeof(T)]);

      *a = *b;
   }

   dataSize = rhs.dataSize;

   return *this;
}


template <class T>
ArrayList<T>::~ArrayList<T>()
{
   for (int i = 0; i < dataSize; i++)
   {
      T* a = reinterpret_cast<T*>(&data[i * sizeof(T)]);
      a->~T();
   }

   if (data != 0)
   {
      delete [] data;
      data = 0;
   }
   
   dataSize = 0;
   dataCapacity = 0;
}

template <class T>
bool
ArrayList<T>::error()
{
   return errflag;
}

template <class T>
void
ArrayList<T>::clear()
{
   // Call the destructors for each instance, and then we'll set the size to zero.
   for (int i = 0; i < dataSize; i++)
   {
      T* a = static_cast<T*>(&data[i]);
      a->~T();
   }   
}
   
   
template <class T>
bool
ArrayList<T>::add(T element)
{
   if (dataSize == dataCapacity)
      return false;

   // Construct a new instance in the next location
   T* a = new (&data[dataSize * sizeof(T)]) T;
   dataSize++;
   
   *a = element;

   return true;
}

template <class T>
bool
ArrayList<T>::put(int index, T element)
{
   if ((index < 0) || (index > (dataSize - 1)))
      return false;

   T* a = reinterpret_cast<T*>(&data[index * sizeof(T)]);

   *a = element;

   return true;   
}

template <class T>
bool
ArrayList<T>::contains(T element)
{
   T curElement = 0;   
   for (int i = 0; i < size(); i++)
   {
      get(i, curElement);
      
      if (curElement == element)
         return true;
   }

   return false;
}

template <class T>
bool
ArrayList<T>::get(int index, T& element) const
{
   if ((index < 0) || (index > (dataSize - 1)))
      return false;

   T* a = reinterpret_cast<T*>(&data[index * sizeof(T)]);

   element = *a;

   return true;
}

template <class T>
bool
ArrayList<T>::indexOf(T element, int& index) const
{
   T curElement = 0;   
   for (int i = 0; i < size(); i++)
   {
      get(i, curElement);
      
      if (curElement == element)
      {
         index = i;
         return true;
      }
   }

   return false;   
}

template <class T>
bool
ArrayList<T>::isEmpty()
{
   return dataSize == 0;
}

template <class T>
bool
ArrayList<T>::remove(int index)
{
   return false;
}

template <class T>
bool
ArrayList<T>::removeElement(T element)
{
   return false;
}

template <class T>
bool
ArrayList<T>::set(int index, T element)
{
   return false;
}

template <class T>
int
ArrayList<T>::size() const
{
   return dataSize;
}

template <class T>
int
ArrayList<T>::capacity() const
{
   return dataCapacity;
}

} // namespace isat_utils

#endif // ARRAYLIST_H
   
