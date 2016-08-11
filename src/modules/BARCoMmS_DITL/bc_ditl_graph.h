#ifndef BC_DITL_GRAPH_H
#define BC_DITL_GRAPH_H

#include <QTreeWidgetItem>
#include <QGraphicsItem>
#include <QDebug>
#include <QList>

#include <vector>

#include "../dependencies/bc_Event.h"
#include "bc_ditl_sevTreeItem.h"

class Graph{
public:
    struct Row
        // Horizontal position reference
    {
        std::string name;
        double y;

        Row(std::string, double);
    };

    struct EventItem
        // Graphics item reference
    {
        BC_Event* event;
        BC_Event pevents;
        BC_Event* peventf;
        BC_DITL_SEVTREE_ITEM* treeItem;

        QGraphicsPixmapItem* unboundedEventArrow;

        enum RectType
        {
            Unstarted,
            Paired,
            Unfinished
        };

        std::vector<QGraphicsItem*> graphicsItems;

        RectType type;

        ~EventItem();
        EventItem(std::vector<QGraphicsEllipseItem*>, BC_Event*);
        EventItem(std::vector<QGraphicsRectItem*>, RectType, BC_Event*);
        EventItem(std::vector<QGraphicsRectItem*>, RectType, BC_Event, BC_Event*);
    };

    // <EventTree>
    QList<QTreeWidgetItem*> topLevelList; // List of tree items at top level (Adv, Cau, War)
    QTreeWidgetItem *Advisory;  // Top level tree item
    QTreeWidgetItem *Caution;  // Top level tree item
    QTreeWidgetItem *Warning; // Top level tree item
    QTreeWidgetItem *Error;  // Top level tree item
    // </EventTree>

    // Grid line coords
    std::vector<double> gridLineX;
    std::vector<double> gridLineY;

    // Event Vector
    std::vector<EventItem*> events;

    // Row information (event name and y coord)
    std::vector<Row> rows;

    // TimeStep, Highest and lowest time (unix epoch (s))
    uint64_t low, high;
    uint64_t timeStep;

    // Last painted timestamp
    QDateTime lastTime;

    // (De/Co)nstructors
    Graph();
    ~Graph();

    // Add this event to the tree list
    void addTreeItem(BC_DITL_SEVTREE_ITEM*, EventItem*);
};

#endif // BC_DITL_GRAPH_H
