#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <string>


namespace isat_utils
{

/**
 * Adaptor for EvenManager. Makes it easy(er) to create and log events.
 */
class EventLogger
{
      
   public:


      /**
       * Create an EventLogger that will log events with the specified origin and file.
       */
      EventLogger(int origin,
                  std::string file);

      
      /**
       * Issue an advisory level point event (single instant in time).
       */
      void advisory(int eventCode,
                    int linenum,                    // Pass __LINE__ for this.
                    std::string message = ""); 

      /**
       * Issue and advisory level range event. This is the start of the range.
       */
      void advisoryStart(int eventCode,
                         int linenum,
                         std::string message = "");


      void advisoryEnd(int eventCode,
                       int linenum,
                       std::string message = "");


   protected:

      int origin;
      std::string file;
                    
};

}  // namespace isat_utils


#endif  // EVENTLOGGER_H
