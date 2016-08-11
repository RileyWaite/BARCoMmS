#include "bc_ditl.h"

#include <QProgressDialog>
#include <QMessageBox>
#include <QScrollBar>

void BC_DITL::repaint(uint64_t newTimeStep)
{
    // Fetch current scene rectangle
    QRectF sRect = graphScene->sceneRect();

    // Clear all objects from graphics scenes
    graphScene->clear();
    timeScene->clear();
    nameScene->clear();

    // Fetch current graph values, delete graph
    Graph tempGraph = *graph;
    delete graph;
    graph = new Graph;

    // Assign new timestep
    graph->timeStep = newTimeStep;

    // Initialize event reference column
    initEventNameList();

    // Add all events back to the graph with new timestep
    if(tempGraph.events.size() >= 1)
    {
        // Initial addEvent with refresh flag true
        if(tempGraph.events.front()->type==Graph::EventItem::RectType::Paired)
        {
            addEvent(&tempGraph.events.front()->pevents, true);
            addEvent(tempGraph.events.front()->peventf);
        }
        else addEvent(tempGraph.events.front()->event, true);

        // Rest of events
        for(unsigned int i(1); i<tempGraph.events.size(); ++i)
        {
            if(tempGraph.events[i]->type==Graph::EventItem::RectType::Paired)
            {
                addEvent(&tempGraph.events[i]->pevents);
                addEvent(tempGraph.events[i]->peventf);
            }
            else addEvent(tempGraph.events[i]->event);

            // Status bar message
            QString msg = QString::fromStdString(tempGraph.events[i]->treeItem->details).replace('\n',';');
            ui->DITL_statusBar->showMessage(QString("Repainting: ").append(msg));
        }
    }
    // Clear statusbar
    ui->DITL_statusBar->clearMessage();

    // Set width of scene rectangle to new width
    sRect.setWidth(graph->gridLineX.back()-graph->gridLineX.front());
    sRect.setTopLeft(QPoint(graph->gridLineX.front(),graph->gridLineY.front()));

    // Assign graphscene rectangle width || TODO: Maybe need another rect for the timescene, so taht user cannot alt-scroll further than actual
    graphScene->setSceneRect(sRect);
}
