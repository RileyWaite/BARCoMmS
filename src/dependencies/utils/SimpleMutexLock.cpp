
#include "isat/utils/SimpleMutexLock.h"

namespace isat_utils
{

SimpleMutexLock::SimpleMutexLock(pthread_mutex_t* mutex)
   : myMutex(mutex)
{
   pthread_mutex_lock(myMutex);
}

SimpleMutexLock::~SimpleMutexLock()
{
   pthread_mutex_unlock(myMutex);
}

}
