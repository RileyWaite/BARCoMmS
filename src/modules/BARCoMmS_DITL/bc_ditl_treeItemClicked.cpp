#include "bc_ditl.h"

#include <QScrollBar>

void BC_DITL::treeItemClicked(QTreeWidgetItem *itemin, int col)
    // Handles setting scene position and highlighting events when tree item is double clicked
{
    // Check to be sure the item is an event description tile
    if(itemin->childCount()==0)
    {
        // Deletes previous highlight
        delete hl;

        // Temporary item to hold contents of QTreeWidgetItem param
        QTreeWidgetItem item = *itemin;

        // Loop until finds a matching event
        for(unsigned int i(0);i<graph->events.size();++i)
        {
            if(graph->events[i]->treeItem->details==item.text(col).toStdString())
            // When it finds the match
            {
                // Scroll to the event graphics object
                ui->DITL_graphicsView->centerOn(graph->events[i]->graphicsItems.back()->boundingRect().topLeft());

                // Below is for drawing highlighting shapes
                if(graph->events[i]->treeItem->isPoint)
                    // Draw an allipse
                {
                    // Draws around current event
                    hl = graphScene->addEllipse(graph->events[i]->treeItem->x, graph->events[i]->treeItem->y, graph->events[i]->treeItem->w, graph->events[i]->treeItem->h,*highlighter,QBrush(QColor(0,0,0,0)));

                    // Used to set invisible after user scrolls away
                    const double x = ui->DITL_graphicsView->horizontalScrollBar()->value();
                    const double y = ui->DITL_graphicsView->verticalScrollBar()->value();

                    // Raise items
                    hl->setZValue(3);
                    for(QGraphicsItem* r:graph->events[i]->graphicsItems) r->setZValue(2);

                    for(;;)
                        // Checks to see if scrolled
                    {
                        qApp->processEvents(); // Qt threading thing (uses Gui thread [ie no worries])
                        if(ui->DITL_graphicsView->horizontalScrollBar()->value() != x ||
                           ui->DITL_graphicsView->verticalScrollBar()->value()   != y   )
                        {
                            hl->setVisible(false);
                            for(QGraphicsItem* r:graph->events[i]->graphicsItems) r->setZValue(1);
                            break;
                        }
                    }
                }
                else
                    // Draw a rectangle
                {
                    // Draws around current event
                    hl = graphScene->addRect(graph->events[i]->treeItem->x, graph->events[i]->treeItem->y, graph->events[i]->treeItem->w, graph->events[i]->treeItem->h,*highlighter,QBrush(QColor(0,0,0,0)));

                    // Used to set invisible after user scrolls away
                    const double x = ui->DITL_graphicsView->horizontalScrollBar()->value();
                    const double y = ui->DITL_graphicsView->verticalScrollBar()->value();

                    // Raise items
                    hl->setZValue(3);
                    for(QGraphicsItem* e:graph->events[i]->graphicsItems) e->setZValue(2);

                    for(;;)
                        // Checks to see if scrolled
                    {
                        qApp->processEvents(); // Qt threading thing (uses Gui thread [ie no worries])
                        if(ui->DITL_graphicsView->horizontalScrollBar()->value() != x ||
                           ui->DITL_graphicsView->verticalScrollBar()->value()   != y   )
                        {
                            hl->setVisible(false);
                            for(QGraphicsItem* e:graph->events[i]->graphicsItems) e->setZValue(1);
                            break;
                        }
                    }
                }
                return;
            }
        }
        // Throw TREE EVENT NULL REFERENCE error
        ditlError("[TREE EVENT NULL REFERENCE]", QString("Event \"").append(itemin->parent()->text(0)).append("\"\ndoes not exist!\n"));
    }
}
