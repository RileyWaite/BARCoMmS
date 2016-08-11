#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <deque>
#include <boost/thread.hpp>
#include "../dependencies/utils/Event.h"

namespace isat_utils
{

class EventManager
{
   public:

      static EventManager& getInstance();

      
      /**
       * Issue a point event (single instant in time).
       */
      void logEvent(Event event);

      /**
       * Returns true if there are events in the event queue.
       */
      bool hasEvents() const;

      /**
       * Gets the next event in the queue, returns true. Returns false if there are no events.
       */
      bool getEvent(Event& event);

      
   protected:

      EventManager();

      std::deque<Event> eventQueue;
      mutable boost::mutex queueMutex;
      
};

}  // namespace isat_utils


#endif  // EVENTMANAGER_H
