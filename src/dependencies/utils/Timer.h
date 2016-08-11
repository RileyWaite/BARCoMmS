#ifndef TIMER_H
#define TIMER_H

namespace isat_utils
{

class Timer
{
   public:

      Timer();
      
      void start();
      void stop();
      void reset();

      long long elapsedTimeInMillis();

      
   protected:

      bool isRunning;
      long long startTime;
      long long elapsedTime;
};

}

#endif // TIMER_H
