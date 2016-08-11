#include "bc_ditl.h"

void BC_DITL::initTimes(uint64_t startTime)
    // Paints bottom graphics scene, which contains the horizontal list of timestamps [UTC]
{
    // Floors to nearest increment and shifts one increment left
    graph->low = startTime-(startTime%graph->timeStep + graph->timeStep);

    // Set "current time" cursor to minumim
    QDateTime cursor = QDateTime::fromTime_t(graph->low);
    cursor.setTimeZone(QTimeZone::utc()); // set as UTC
    cursor.setTimeSpec(Qt::UTC);

    // Coordinate variables
    const double y=1;
    const double x=0;

    // Push back grid line vector with new x coords and draw vertical lines
    graph->gridLineX.push_back(x);
    graphScene->addRect(x,graph->gridLineY.front()-2,0,graph->gridLineY.back()-graph->gridLineY.front(),*linePen)->setZValue(0);
    graph->gridLineX.push_back(x+TIMESLOT_WIDTH);
    graphScene->addRect(x+TIMESLOT_WIDTH,graph->gridLineY.front()-2,0,graph->gridLineY.back()-graph->gridLineY.front(),*linePen)->setZValue(0);

    // Draw the timestamp bounding rectangle
    timeScene->addRect(x,y,TIMESLOT_WIDTH,(0.94)*ui->DITL_graphicsView_BOTT->height(),*outlinePen);

    // Grab time as a string and format it a bit
    std::string timestamp = cursor.toString(Qt::ISODate).toStdString();
    for(unsigned char i(0); i<timestamp.size();++i){ if(timestamp[i]=='T') { timestamp[i]='\n'; break; } }
    if(timestamp.back()=='Z') timestamp.pop_back();

    // Add text to the rectangle
    QGraphicsTextItem *text;
    text = timeScene->addText(QString::fromStdString(timestamp), *timeFont);
    text->setDefaultTextColor(QColor(205,201,201));
    text->setPos(x,y);

    // Add tooltip text containing several time formats
    QString tt = "UTC: ";
    tt.append(cursor.toString());
    tt.append("\nLocal: ").append(cursor.toLocalTime().toString(Qt::SystemLocaleShortDate));
    text->setToolTip(tt);

    // Progress the cursor forward
    cursor = cursor.addSecs(graph->timeStep);

    // Push back grid line vector with one last line (all of the junk after (slotcount*) is dt)
//    graph->gridLineX.push_back(slotCount*TIMESLOT_WIDTH+(0.5*TIMESLOT_WIDTH));
//    graphScene->addRect(graph->gridLineX.back(),graph->gridLineY.front()-2,0,graph->gridLineY.back()-graph->gridLineY.front(),*linePen)->setZValue(0);

    // Set lastTime to current cursor so that we can add more timeslots later
    graph->lastTime = cursor;
}
