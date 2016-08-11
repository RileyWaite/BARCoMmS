#include "bc_Event.h"

#include <sstream>
#include <QDebug>

BC_Event::BC_Event (uint64_t time /* as ms */, int code, int origin,
             int eventType, int severity,
             std::string message,
             std::string filename, int lineNumber)
    // TODO: Configure this to take ms instead of s (requires regeneration of trek classes)
{
    this->time=time;
    this->code=code;
    this->origin=origin;
    this->eventType=static_cast<EventType>(eventType);
    this->severity=static_cast<Severity>(severity);
    this->message=message;
    this->filename=filename;
    this->lineNumber=lineNumber;
}

BC_Event::BC_Event(std::string in) { read(in);}

QDateTime BC_Event::getUTC()
{
    QDateTime datetime = QDateTime::fromTime_t(this->time);
    datetime.setTimeZone(QTimeZone::utc());
    datetime.setTimeSpec(Qt::UTC);

    return datetime;
}

QDateTime BC_Event::getUTC(uint64_t time)
{
    QDateTime datetime = QDateTime::fromTime_t(time);
    datetime.setTimeZone(QTimeZone::utc());
    datetime.setTimeSpec(Qt::UTC);

    return datetime;
}

bool BC_Event::write(std::fstream& out)
{
    if(!out.is_open())
    {
        fprintf(stderr, "Filestream not open for event data write; Escaping the write.\n");
        return false;
    }

    std::stringstream buf;
    buf << time*1000 << ' '
        << code << ' '
        << origin << ' '
        << eventType << ' '
        << severity << ' '
        << lineNumber << ' '
        << filename << ' '
        << message;

    out << buf.str() << std::endl;
    out.write(buf.str().c_str(), sizeof buf.str().c_str());
    out.flush();
    return true;
}

bool BC_Event::read(std::string in)
{
    std::string t, c, o, e, s, l;
    std::stringstream ss;
    ss << in;

    ss  >> t
        >> c
        >> o
        >> e
        >> s
        >> l
        >> filename;

    time = std::stoul(t)/1000;
    code = std::stoi(c);
    origin = std::stoi(o);
    switch(std::stoi(e))
    {
    case 0:
        eventType = EventType::POINT;
        break;
    case 1:
        eventType = EventType::START;
        break;
    case 2:
        eventType = EventType::END;
        break;
    }
    switch(std::stoi(s))
    {
    case 0:
        severity = Severity::ADVISORY;
        break;
    case 1:
        severity = Severity::CAUTION;
        break;
    case 2:
        severity = Severity::WARNING;
        break;
    }
    lineNumber = std::stoi(l);


    std::getline(ss,message);
    return true;
}
