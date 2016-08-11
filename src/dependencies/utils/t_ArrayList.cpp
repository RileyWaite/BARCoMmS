
#include <iostream>
#include "isat/utils/ArrayList.h"
#include "isat/utils/String.h"

using namespace std;
using namespace isat_utils;

template <class T>
void
printone(int index, ArrayList<T>& array)
{
   T tmpval;
   array.get(index, tmpval);
   cout << index << ": " << tmpval << "\n";
}

int
main(int argc, char** argv)
{
#if 0   
   ArrayList<int> intlist;

   cout << "This is a test of the ArrayList template.\n";

   intlist.add(100);
   intlist.add(100);
   intlist.add(2112);


   cout << "size: " << intlist.size() << "\n";
   cout << "capacity: " << intlist.capacity() << "\n";

   printone(0, intlist);

   printone(1, intlist);

   printone(2, intlist);


   cout << "Assigning to another array...\n";
   ArrayList<int> b;
   b = intlist;

   printone(0, b);
   printone(1, b);
   printone(2, b);

   cout << "Array of Strings...\n";

   ArrayList<String> foo;
   foo.add("jamie");
   foo.add("pip");
   foo.add("rosie");

   printone(0, foo);
   printone(1, foo);
   printone(2, foo);
#endif
   ArrayList<String> baz;
   baz.add("dog");
   baz.add("giraffe");
   baz.add("lizard");

   ArrayList<String> xyzzy;
   xyzzy = baz;
   
   
}
