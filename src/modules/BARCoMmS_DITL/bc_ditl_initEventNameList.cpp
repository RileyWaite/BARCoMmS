#include "bc_ditl.h"

#include <QScrollBar>

void BC_DITL::initEventNameList()
    // Paints left-most graphics scene, which contains the list of events found in the event reference file
{
    // Coordinate variables
    const double dy=eventHeight+3, // Const
                 x=-4; // Const
    double       y; // Changes (vertical list)

    for(unsigned int i(0);i<db.eventDB.size();++i)
        // For every event in reference event database
    {
        // Send status message
        ui->DITL_statusBar->showMessage(QString("Painting event reference column (").append(QString::number(100*(double)i/db.eventDB.size())).append("%)"));
        y = (((1-eventHeight)/2)*dy)+(i*dy); // Next y coord

        // Add the rectangle to the scene
        nameScene->addRect(x,y,(0.99)*ui->DITL_graphicsView_LEFT->width(),eventHeight,*outlinePen,colorDB.colorFromEvent(db.eventDB[i].name));

        // Push back the grid line vector with this y coord
        graph->gridLineY.push_back(y);

        // Add the text to this rectangle
        QGraphicsTextItem *text;
        text = nameScene->addText(QString::fromStdString(db.eventDB[i].name), *eventFont);
        text->setPos(x,y+(eventHeight/8)-3);
        text->setDefaultTextColor(Qt::black);

        // Push back the "rows" with struct for later referencing a y location from an event string
        graph->rows.push_back(Graph::Row(db.eventDB[i].name,y));

        // This handles strings larger than the width of the rectangle
        std::string tempt = db.eventDB[i].name + "...";
        while(text->boundingRect().width()>ui->DITL_graphicsView_LEFT->width())
            // While the string is wider than the rectangle
        {
            // Back that ass up and re-elipses it
            tempt.pop_back();
            tempt.pop_back();
            tempt.pop_back();
            tempt.pop_back();

            tempt += "...";

            // Update the text
            text->setToolTip(QString::fromStdString(db.eventDB[i].name));
            text->setPlainText(QString::fromStdString(tempt));
            text->update();
        }
    }

    // Clear status bar
    ui->DITL_statusBar->clearMessage();

    // Push back the grid line vector one last line to complete the grid
    graph->gridLineY.push_back(y+dy);

    // Add small rectangle to resize nameScene to align with graphScene (compensates for scrollbar)
    nameScene->addRect(x,graph->gridLineY.back(),(0.99)*ui->DITL_graphicsView_LEFT->width(),13,QPen(QColor(0,0,0,0)));
}
