
#include "isat/utils/EventManager.h"

namespace isat_utils
{

EventManager::EventManager()
{
}

EventManager&
EventManager::getInstance()
{
   static EventManager instance;

   return instance;
}


void
EventManager::logEvent(Event event)
{
   boost::lock_guard<boost::mutex> guard(queueMutex);

   eventQueue.push_back(event);
}


bool
EventManager::hasEvents() const
{
   boost::lock_guard<boost::mutex> guard(queueMutex);

   return !eventQueue.empty();
}


bool
EventManager::getEvent(Event& event)
{
   boost::lock_guard<boost::mutex> guard(queueMutex);
   
   if (eventQueue.empty())
      return false;

   event = eventQueue.front();
   eventQueue.pop_front();

   return true;
}


}  // namespace isat_utils
