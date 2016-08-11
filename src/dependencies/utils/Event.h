fndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <string>

namespace isat_utils
{

class Event
{
public:
    enum Severity { ADVISORY = 0,
                    CAUTION = 1,
                    WARNING = 2 };

    enum EventType { POINT = 0,    // Single instant in time
                     START = 1,
                     END = 2 };   // Start of an interval

    uint64_t time;  // Time event occured in milliseconds unix epoch.
    int code;    // What's the event represent (From EventCodes.h)
    int origin;  // Who logged the event?
    EventType eventType;
    Severity severity;
    std::string message;
    std::string filename;
    int lineNumber;

    // BELOW IS FOR TESTING

    Event // This is going to automatically convert ms -> s, since every other static method takes s.
    (uint64_t time, int code, int origin,
                 EventType eventType, Severity severity,
                 std::string message,
                 std::string filename, int lineNumber)
    {
        this->time=time/1000;
        this->code=code;
        this->origin=origin;
        this->eventType=eventType;
        this->severity=severity;
        this->message=message;
        this->filename=filename;
        this->lineNumber=lineNumber;
    }
};

}

#endif  // EVENT_H
