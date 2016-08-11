#include "bc_ditl.h"

#include <QScrollBar>

void BC_DITL::addEvent(BC_Event* event, bool refresh)
{
    // Write the event's data to the event file
    event->write(eventFile);

    // Initialize Times
    static bool init = true;
    if(init||refresh)
    {
        initTimes(event->time);
        init = false;
    }

    // Declare the reference event offset (in the graph->rows struct vector
    unsigned short REFEVNT_OFF=0;

    // Create an event object to hold the current event's information from the event database
    EventDatabase::Event currEvent;

    // Grab info from database
    if(!db.getEvent(event->code, currEvent)) qDebug() << "Could not reference event ID (" << event->code << ")\n\n";

    // Create an origin object for the same reason
    EventDatabase::Origin currOrig;

    // Grab info from database
    if(!db.getOrigin(event->origin, currOrig)) qDebug() << "Could not reference origin ID (" << event->origin << ")\n\n";

    // Send status message
    ui->DITL_statusBar->showMessage(QString("Creating event for ID: ").append(QString::fromStdString(currEvent.name)).append(" (").append(QString::number(event->code)).append(")"));

    for(unsigned short j(0);j<graph->rows.size();++j)
        // Find the matching event in the vertical event list
    {
        if(currEvent.name == graph->rows[j].name)
            // Set the reference event offset
        {
            REFEVNT_OFF=j;
            break;
        }
    }


    // ===== PAINT ===== //

    if(event->getUTC() > graph->lastTime)
        // Time Expansion and Current Unfinished Rectangle Repaint
    {
        // Coordinate variable
        double x = graph->gridLineX.back();

        //for(unsigned short i(0); i<slotcount; ++i)
        while(event->getUTC() > graph->lastTime)
            // Loop until past the event
        {
            // Draw the timestamp bounding rectangle
            timeScene->addRect(x,1,TIMESLOT_WIDTH,(0.94)*ui->DITL_graphicsView_BOTT->height(),*outlinePen);

            // Grab time as a string and format it a bit
            std::string timestamp = graph->lastTime.toString(Qt::ISODate).toStdString();
            for(unsigned char i(0); i<timestamp.size();++i){ if(timestamp[i]=='T') { timestamp[i]='\n'; break; } }
            if(timestamp.back()=='Z') timestamp.pop_back();

            // Add text to the rectangle
            QGraphicsTextItem *text;
            text = timeScene->addText(QString::fromStdString(timestamp), *timeFont);
            text->setDefaultTextColor(QColor(205,201,201));
            text->setPos(x,1);

            // Add tooltip text containing several time formats
            QString tt = "UTC: ";
            tt.append(graph->lastTime.toString());
            tt.append("\nLocal: ").append(graph->lastTime.toLocalTime().toString(Qt::SystemLocaleShortDate));
            text->setToolTip(tt);

            // Add Another Grid Line
            graph->gridLineX.push_back(x);
            graphScene->addRect(x,graph->gridLineY.front()-2,0,graph->gridLineY.back()-graph->gridLineY.front(),*linePen)->setZValue(0);

            // Progress the graph->lastTime
            graph->lastTime = graph->lastTime.addSecs(graph->timeStep);

            // Progress x coord
            x += TIMESLOT_WIDTH;
        }

        // Draw last vertical line
        graph->gridLineX.push_back(graph->gridLineX.back()+TIMESLOT_WIDTH);
        graphScene->addRect(x,graph->gridLineY.front()-2,0,graph->gridLineY.back()-graph->gridLineY.front(),*linePen)->setZValue(0);

        // Draw cube at end of timescene to make room for main scene's vertical scrollbar
        if(ui->DITL_graphicsView->verticalScrollBar()->isVisible())
        {
            // Instantiate buffer cube
            static QGraphicsRectItem* bufferCube = new QGraphicsRectItem;
            if(!refresh) delete bufferCube;
            bufferCube = timeScene->addRect(graph->gridLineX.back(),1,16,(0.94)*ui->DITL_graphicsView_BOTT->height(),QPen(QColor(0,0,0,0)));
        }

        // Horizontal Line Repaint
        for(unsigned int i(0);i<graph->gridLineY.size();++i) graphScene->addRect(0,graph->gridLineY[i]-2,graph->gridLineX.back(),0,*linePen)->setZValue(0);

        for(unsigned int i(0); i<graph->events.size(); ++i)
            // Stretch out all of the unfinished rectangles
        {
            if(graph->events[i]->type == Graph::EventItem::RectType::Unfinished)
                // For every unfinished rectangle
            {
                // Clear old rectangle
                for(unsigned char j(0); j<graph->events[i]->graphicsItems.size(); ++j) graphScene->removeItem(graph->events[i]->graphicsItems[j]);
                graph->events[i]->graphicsItems.clear();

                // Declare the reference event offset (in the graph->rows struct vector
                unsigned short REFEVNT_OFF=0;

                // Create an event object to hold the current event's information from the event database
                EventDatabase::Event currEvent;

                // Grab info from database
                if(!db.getEvent(graph->events[i]->event->code, currEvent)) qDebug() << "Could not reference event ID (" << graph->events[i]->event->code << ")\n\n";

                // Create an origin object for the same reason
                EventDatabase::Origin currOrig;

                // Grab info from database
                if(!db.getOrigin(graph->events[i]->event->origin, currOrig)) qDebug() << "Could not reference origin ID (" << graph->events[i]->event->origin << ")\n\n";

                for(unsigned short j(0);j<graph->rows.size();++j)
                    // Find the matching event in the vertical event list
                {
                    if(currEvent.name == graph->rows[j].name)
                        // Set the reference event offset
                    {
                        REFEVNT_OFF=j;
                        break;
                    }
                }


                // Vectors holds references to all graphics items
                std::vector<QGraphicsRectItem*> rectangles;

                // "cursor" is the horizontal location of event in 'timeslots'
                double cursor = (double)(graph->events[i]->event->time-graph->low)/graph->timeStep;
                // Which is then multiplied by the width of a timeslot
                double x = cursor*TIMESLOT_WIDTH;

                // Set color (grabbed by event name)
                QBrush color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

                if(graph->events[i]->event->severity==BC_Event::Severity::CAUTION)
                    // Red dotted foreground if CAUTION
                {
                    // Draw original rectangle
                    // NOTE: width parameter = (total scene width)-(starting position)
                    // Since it is an "unfinished" event, it goes until the end of the scene
                    rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

                    // Set color to red warning
                    color = colorDB.colorFromString("WARN");
                    color.setStyle(Qt::Dense7Pattern);

                    // Draw dotted foreground over original rectangle
                    rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));
                }
                if(graph->events[i]->event->severity==BC_Event::Severity::WARNING)
                    // Draw crossed red foreground and outline if WARNING
                {
                    // Change color to non-opaque
                    color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

                    // Draw original rectangle
                    rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

                    // Change color to red warning
                    color = colorDB.colorFromString("WARN");
                    color.setStyle(Qt::DiagCrossPattern);

                    // Draw red crossed and outlined rectangle over original
                    rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*warningPen,color));
                }
                else
                    // Draw original if ADVISORY
                    rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

                // Grab time as string and convert to UTC
                QDateTime temp = QDateTime::fromTime_t(graph->events[i]->event->time);
                temp.setTimeZone(QTimeZone::utc());
                temp.setTimeSpec(Qt::UTC);

                // Define tooltip
                QString tooltip = QString::fromStdString(graph->rows[REFEVNT_OFF].name
                                 ).append(" from: ("
                                 ).append(temp.toString()
                                 ).append(")"
                                 ).append(" -> (UNFINISHED)"
                                 ).append("\nSev: "
                                 ).append(sevToQString(graph->events[i]->event->severity)
                                 ).append("\tMsg: \""
                                 ).append(QString::fromStdString(graph->events[i]->event->message)
                                 ).append("\"\nSource: "
                                 ).append(" ").append(QString::fromStdString(currOrig.name)
                                 ).append(" from "
                                 ).append(QString::fromStdString(graph->events[i]->event->filename)
                                 ).append(" on line "
                                 ).append(QString::number(graph->events[i]->event->lineNumber));

                // Set event's tooltip
                rectangles.back()->setToolTip(tooltip);
                for(QGraphicsRectItem* r:rectangles) r->setZValue(1);

                // Delete old unbounded arrow
                delete graph->events[i]->unboundedEventArrow;

                // Reassign the event
                graph->events[i] = new Graph::EventItem(rectangles, Graph::EventItem::Unfinished, graph->events[i]->event);

                // Add this item to the event tree
                // TODO: REPLACE OLD ONE SOMEHOW
                graph->events[i]->treeItem = new BC_DITL_SEVTREE_ITEM(graph->events[i]->event->severity,
                                                    graph->rows[REFEVNT_OFF].name,
                                                    tooltip.toStdString(),
                                                    x,
                                                    graph->gridLineY[REFEVNT_OFF],
                                                    graph->gridLineX.back()-x,
                                                    eventHeight,
                                                    false);

                // Add new unbounded arrow
                graph->events[i]->unboundedEventArrow = graphScene->addPixmap(*unboundedArrowRight);
                graph->events[i]->unboundedEventArrow->setPos(graph->gridLineX.back()-45,graph->gridLineY[REFEVNT_OFF]-1);
                graph->events[i]->unboundedEventArrow->setZValue(2);
            }
        }
    }


    if(event->eventType==BC_Event::EventType::POINT)
        // Paint a point event
    {
        // Vectors holds references to all graphics items
        std::vector<QGraphicsEllipseItem*> ellipses;

        // "cursor" is the horizontal location of event in 'timeslots'
        double cursor = ((double)(event->time-graph->low))/graph->timeStep;

        // Which is then multiplied by the width of a timeslot and shifted to the left
        double x = (cursor*TIMESLOT_WIDTH)-eventHeight/2;

        // The y coordinate is grabbed from the graph information singleton
        double y = graph->rows[REFEVNT_OFF].y;

        // Grab color from the origin color reference file (based on event)
        QBrush color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

        if(event->severity==BC_Event::Severity::CAUTION)
            // Paint a red-dotted foreground over the event
        {
            // Draw original Ellipse
            ellipses.push_back(graphScene->addEllipse(x,y,eventHeight,eventHeight,*outlinePen,color));

            // Change color params to red
            color = colorDB.colorFromString("WARN");
            color.setStyle(Qt::Dense7Pattern);

            // Draw dotted foreground over original
            ellipses.push_back(graphScene->addEllipse(x,y,eventHeight,eventHeight,*outlinePen,color));
        }

        else if(event->severity==BC_Event::Severity::WARNING)
            // Paint a red-crossed foreground and outline in red
        {
            // Set original color to non-opaque
            color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

            // Draw original ellipse
            ellipses.push_back(graphScene->addEllipse(x,y,eventHeight,eventHeight,*outlinePen,color));

            // Change color to red
            color = colorDB.colorFromString("WARN");
            color.setStyle(Qt::DiagCrossPattern);

            // Draw outline and crossed foreground
            ellipses.push_back(graphScene->addEllipse(x,y,eventHeight,eventHeight,*warningPen,color));
        }
        else
            // Draws the original ellipse only
            ellipses.push_back(graphScene->addEllipse(x,y,eventHeight,eventHeight,*outlinePen,color));

        // Define tooltip string
        QString tooltip = QString::fromStdString(
                    currEvent.name + " @ ("
                    ).append(event->getUTC().toString()
                    ).append(")\nSev: "
                    ).append(sevToQString(event->severity)
                    ).append("\tMsg: \""
                    ).append(QString::fromStdString(event->message)
                    ).append("\"\nSource: "
                    ).append(" ").append(QString::fromStdString(currOrig.name)
                    ).append(" from "
                    ).append(QString::fromStdString(event->filename)
                    ).append(" on line "
                    ).append(QString::number(event->lineNumber));

        // Set the event's tooltip
        ellipses.back()->setToolTip(tooltip);
        for(QGraphicsEllipseItem* e:ellipses) e->setZValue(1);

        // Push back the graphics item reference vector
        graph->events.push_back(new Graph::EventItem(ellipses, event));

        // Add this item to the event tree
        graph->addTreeItem(new BC_DITL_SEVTREE_ITEM(event->severity,
                                            graph->rows[REFEVNT_OFF].name,
                                            tooltip.toStdString(),
                                            x,
                                            y,
                                            eventHeight,
                                            eventHeight,
                                            true),
                    graph->events.back());
    }


    else if(event->eventType==BC_Event::EventType::END)
        // Paints an unstarted event or completes an unfinished event
    {
        // Paired flag to throw unstarted error
        bool paired = false;

        for(unsigned short i(0); i<graph->events.size(); ++i)
            // Check if there's an unfinished event waiting for this
        {
            if(event->code==graph->events[i]->event->code &&
                graph->events[i]->type == Graph::EventItem::RectType::Unfinished)
                // If it finds a match
            {
                //Set paired flag to avoid throwing unstarted error
                paired = true;
                // Clear old rectangle
                for(unsigned char j(0); j<graph->events[i]->graphicsItems.size(); ++j) graphScene->removeItem(graph->events[i]->graphicsItems[j]);
                graph->events[i]->graphicsItems.clear();

                // Vectors holds references to all graphics items
                std::vector<QGraphicsRectItem*> rectangles;

                // Similar procedure here, but we mark cursors for the beginning and end times
                double start = ((double)(graph->events[i]->event->time-graph->low)/graph->timeStep)*TIMESLOT_WIDTH;
                double end = ((double)(event->time-graph->low)/graph->timeStep)*TIMESLOT_WIDTH;

                // Initialize the color (grabs by event name)
                QBrush color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

                if(event->severity==BC_Event::Severity::CAUTION)
                    // Paints a dotted red foreground if CAUTION
                {
                    // Original rectangle
                    rectangles.push_back(graphScene->addRect(start,graph->gridLineY[REFEVNT_OFF],end-start,eventHeight,*outlinePen,color));

                    // Change color to red warning
                    color = colorDB.colorFromString("WARN");
                    color.setStyle(Qt::Dense7Pattern);

                    // Draw dotted foreground over original rectangle
                    rectangles.push_back(graphScene->addRect(start,graph->gridLineY[REFEVNT_OFF],end-start,eventHeight,*outlinePen,color));
                }

                else if(event->severity==BC_Event::Severity::WARNING)
                    // Draws a crossed foreground and red outline if WARNING
                {
                    // Change color to non-opaque
                    color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

                    // Draw original rectangle
                    rectangles.push_back(graphScene->addRect(start,graph->gridLineY[REFEVNT_OFF],end-start,eventHeight,*outlinePen,color));

                    // Change color to red warning
                    color = colorDB.colorFromString("WARN");
                    color.setStyle(Qt::DiagCrossPattern);

                    // Draw red outline and crossed patterned rectangle over original rectangle
                    rectangles.push_back(graphScene->addRect(start,graph->gridLineY[REFEVNT_OFF],end-start,eventHeight,*warningPen,color));
                }

                else
                    // Draw the original rectangle if ADVISORY
                    rectangles.push_back(graphScene->addRect(start,graph->gridLineY[REFEVNT_OFF],end-start,eventHeight,*outlinePen,color));

                // Grab event time as string and convert to UTC
                QDateTime temp = QDateTime::fromTime_t(graph->events[i]->event->time);
                temp.setTimeZone(QTimeZone::utc());
                temp.setTimeSpec(Qt::UTC);

                // Define tooltip
                QString tooltip = QString::fromStdString(graph->rows[REFEVNT_OFF].name
                                 ).append(" from: ("
                                 ).append(temp.toString()
                                 ).append(") -> ("
                                 ).append(event->getUTC().toString()
                                 ).append(")\nSev: "
                                 ).append(sevToQString(event->severity)
                                 ).append("\tMsg: \""
                                 ).append(QString::fromStdString(event->message)
                                 ).append("\"\nSource: "
                                 ).append(" ").append(QString::fromStdString(currOrig.name)
                                 ).append(" from "
                                 ).append(QString::fromStdString(event->filename)
                                 ).append(" on line "
                                 ).append(QString::number(event->lineNumber));

                // Set event's tooltip
                rectangles.back()->setToolTip(tooltip);
                for(QGraphicsRectItem* r:rectangles) r->setZValue(1);

                // Grab a by-value copy of the event to store in the "paired" event object
                BC_Event tempEventItem = *graph->events[i]->event;

                // Delete the graph item to remove it from tree
                delete graph->events[i];

                // Push back the event item reference vector
                graph->events[i] = new Graph::EventItem(rectangles, Graph::EventItem::Paired, tempEventItem, event);

                // Push back the tree item vector with relevant params for later
                graph->addTreeItem(new BC_DITL_SEVTREE_ITEM(event->severity,
                                                    graph->rows[REFEVNT_OFF].name,
                                                    tooltip.toStdString(),
                                                    start,
                                                    graph->gridLineY[REFEVNT_OFF],
                                                    end-start,
                                                    eventHeight,
                                                    false),
                                  graph->events[i]);
            }
        }

        if(!paired)
        {
            // Vectors holds references to all graphics items
            std::vector<QGraphicsRectItem*> rectangles;

            // "cursor" is the horizontal location of the END of the event in 'timeslots'
            double cursor = (double)(event->time-graph->low)/graph->timeStep;

            //Rectangle width is equal to the distance from the beginining of time to the end event
            double width = cursor*TIMESLOT_WIDTH;

            // Grab color from the origin color reference file (based on event)
            QBrush color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

            if(event->severity==BC_Event::Severity::CAUTION)
                // Paints a red-dotted foreground over the event
            {
                // Draw original rectangle
                rectangles.push_back(graphScene->addRect(graph->gridLineX.front()+2,graph->gridLineY[REFEVNT_OFF],width,eventHeight,*outlinePen,color));

                // Change colors to red
                color = colorDB.colorFromString("WARN");
                color.setStyle(Qt::Dense7Pattern);

                // Draw dotted rectangle over original
                rectangles.push_back(graphScene->addRect(graph->gridLineX.front()+2,graph->gridLineY[REFEVNT_OFF],width,eventHeight,*outlinePen,color));
            }

            else if(event->severity==BC_Event::Severity::WARNING)
                // Draws red outline and crossed foreground over event
            {
                // Set color to non-opaque
                color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

                // Draw original non-opaque rectangle
                rectangles.push_back(graphScene->addRect(graph->gridLineX.front()+2,graph->gridLineY[REFEVNT_OFF],width,eventHeight,*outlinePen,color));

                // Change colors to red
                color = colorDB.colorFromString("WARN");
                color.setStyle(Qt::DiagCrossPattern);

                // Overlay crossed and outlined rectangle over original
                rectangles.push_back(graphScene->addRect(graph->gridLineX.front()+2,graph->gridLineY[REFEVNT_OFF],width,eventHeight,*warningPen,color));
            }
            else
                // Draw original rectangle
                rectangles.push_back(graphScene->addRect(graph->gridLineX.front()+2,graph->gridLineY[REFEVNT_OFF],width,eventHeight,*outlinePen,color));

            // Define tooltip text
            QString tooltip = QString::fromStdString(
                         graph->rows[REFEVNT_OFF].name
                         ).append(" from: (PREVIOUS LOG) -> ("
                         ).append(event->getUTC().toString()
                         ).append(")\nSev: "
                         ).append(sevToQString(event->severity)
                         ).append("\tMsg: \""
                         ).append(QString::fromStdString(event->message)
                         ).append("\"\nSource: "
                         ).append(" ").append(QString::fromStdString(currOrig.name)
                         ).append(" from "
                         ).append(QString::fromStdString(event->filename)
                         ).append(" on line "
                         ).append(QString::number(event->lineNumber));

            // Set event tooltip
            rectangles.back()->setToolTip(tooltip);
            for(QGraphicsRectItem* r:rectangles) r->setZValue(1);

            // Push back the graphics item reference vector
            graph->events.push_back(new Graph::EventItem(rectangles, Graph::EventItem::RectType::Unstarted, event));

            // Push back treeitems vector with relevant parameters for later
            graph->addTreeItem(new BC_DITL_SEVTREE_ITEM(event->severity,
                                                graph->rows[REFEVNT_OFF].name,
                                                tooltip.toStdString(),
                                                graph->gridLineX.front()+2,
                                                graph->gridLineY[REFEVNT_OFF],
                                                width,
                                                eventHeight,
                                                false),
                    graph->events.back());

            // Add unbounded arrow
            graph->events.back()->unboundedEventArrow = graphScene->addPixmap(*unboundedArrowRight);
            graph->events.back()->unboundedEventArrow->setPos(graph->gridLineX.front()+47,graph->gridLineY[REFEVNT_OFF]+44);
            graph->events.back()->unboundedEventArrow->setZValue(2);

            // Rotate to face left
            graph->events.back()->unboundedEventArrow->setRotation(180);
        }
    }

    else if(event->eventType==BC_Event::EventType::START)
    {
        // Vectors holds references to all graphics items
        std::vector<QGraphicsRectItem*> rectangles;

        // "cursor" is the horizontal location of event in 'timeslots'
        double cursor = (double)(event->time-graph->low)/graph->timeStep;
        // Which is then multiplied by the width of a timeslot
        double x = cursor*TIMESLOT_WIDTH;

        // Set color (grabbed by event name)
        QBrush color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

        if(event->severity==BC_Event::Severity::CAUTION)
            // Red dotted foreground if CAUTION
        {
            // Draw original rectangle
            // NOTE: width parameter = (total scene width)-(starting position)
            // Since it is an "unfinished" event, it goes until the end of the scene
            rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

            // Set color to red warning
            color = colorDB.colorFromString("WARN");
            color.setStyle(Qt::Dense7Pattern);

            // Draw dotted foreground over original rectangle
            rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));
        }
        if(event->severity==BC_Event::Severity::WARNING)
            // Draw crossed red foreground and outline if WARNING
        {
            // Change color to non-opaque
            color = colorDB.colorFromEvent(graph->rows[REFEVNT_OFF].name);

            // Draw original rectangle
            rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

            // Change color to red warning
            color = colorDB.colorFromString("WARN");
            color.setStyle(Qt::DiagCrossPattern);

            // Draw red crossed and outlined rectangle over original
            rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*warningPen,color));
        }
        else
            // Draw original if ADVISORY
            rectangles.push_back(graphScene->addRect(x,graph->gridLineY[REFEVNT_OFF],graph->gridLineX.back()-x,eventHeight,*outlinePen,color));

        // Grab time as string and convert to UTC
        QDateTime temp = QDateTime::fromTime_t(event->time);
        temp.setTimeZone(QTimeZone::utc());
        temp.setTimeSpec(Qt::UTC);

        // Define tooltip
        QString tooltip = QString::fromStdString(graph->rows[REFEVNT_OFF].name
                         ).append(" from: ("
                         ).append(temp.toString()
                         ).append(")"
                         ).append(" -> (UNFINISHED)"
                         ).append("\nSev: "
                         ).append(sevToQString(event->severity)
                         ).append("\tMsg: \""
                         ).append(QString::fromStdString(event->message)
                         ).append("\"\nSource: "
                         ).append(" ").append(QString::fromStdString(currOrig.name)
                         ).append(" from "
                         ).append(QString::fromStdString(event->filename)
                         ).append(" on line "
                         ).append(QString::number(event->lineNumber));

        // Set event's tooltip
        rectangles.back()->setToolTip(tooltip);
        for(QGraphicsRectItem* r:rectangles) r->setZValue(1);

        // Push back the event item reference vector
        graph->events.push_back(new Graph::EventItem(rectangles, Graph::EventItem::Unfinished, event));

        // Add this item to the event tree
        graph->addTreeItem(new BC_DITL_SEVTREE_ITEM(event->severity,
                                            graph->rows[REFEVNT_OFF].name,
                                            tooltip.toStdString(),
                                            x,
                                            graph->gridLineY[REFEVNT_OFF],
                                            graph->gridLineX.back()-x,
                                            eventHeight,
                                            false),
                          graph->events.back());

        // Add arrow to display that the event was unfinished
        graph->events.back()->unboundedEventArrow = graphScene->addPixmap(*unboundedArrowRight);
        graph->events.back()->unboundedEventArrow->setPos(graph->gridLineX.back()-45,graph->gridLineY[REFEVNT_OFF]-1);
        graph->events.back()->unboundedEventArrow->setZValue(2);
    }

    // Clear status message
    ui->DITL_statusBar->clearMessage();
}
