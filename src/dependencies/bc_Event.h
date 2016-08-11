#ifndef BC_EVENT_H
#define BC_EVENT_H

#include <QTimeZone>
#include <QDateTime>
#include <QObject>

#include <fstream>

class BC_Event
{
public:
    enum Severity { ADVISORY = 0,
                    CAUTION = 1,
                    WARNING = 2 };

    enum EventType { POINT = 0,    // Single instant in time
                     START = 1,
                     END = 2 };   // Ranged

    uint64_t time;  // Time event occured in seconds unix epoch.
    int code;    // What's the event represent (From EventCodes.h)
    int origin;  // Who logged the event?
    EventType eventType;
    Severity severity;
    std::string message;
    std::string filename;
    int lineNumber;


    BC_Event(){}
    BC_Event(uint64_t, int, int,
             int, int,
             std::string,
             std::string, int);
    BC_Event(std::string in);

    QDateTime getUTC();
    static QDateTime getUTC(uint64_t);

    bool read(std::string in);
    bool write(std::fstream &out);
};

#endif // BC_EVENT_H
