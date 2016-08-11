
#include "isat/utils/Timer.h"
#include "isat/utils/System.h"

namespace isat_utils
{

Timer::Timer()
{
   isRunning = false;
   startTime = 0;
   elapsedTime = 0;
}

void
Timer::start()
{
   startTime = System::getTimeInMilliseconds();
   isRunning = true;
}

void
Timer::stop()
{
   if (isRunning)
      elapsedTime = System::getTimeInMilliseconds() - startTime;
}

void
Timer::reset()
{
   elapsedTime = 0;   
   startTime = System::getTimeInMilliseconds();
}

long long
Timer::elapsedTimeInMillis()
{
   if (!isRunning)
      return elapsedTime;
   
   return elapsedTime + (System::getTimeInMilliseconds() - startTime);
}

}
