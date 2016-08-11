#ifndef SIMPLEMUTEX_H
#define SIMPLEMUTEX_H

#include <pthread.h>

namespace isat_utils
{

// Simple wrapper around pthread mutex that automagically unlocks when the lock is destroyed.
// The mutex is locked in the constructor and unlocked in the destructor.
class SimpleMutexLock
{
   public:

      SimpleMutexLock(pthread_mutex_t* mutex);
      ~SimpleMutexLock();

   protected:
      
      pthread_mutex_t* myMutex;
};

   
} // namespace isat_utils


#endif // SIMPLEMUTEX_H
