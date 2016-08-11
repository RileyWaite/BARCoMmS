#include "bc_ditl.h"
#include "../dependencies/bc_Event.h"

Graph::Graph()
{
    lastTime.setTimeZone(QTimeZone::utc());
    lastTime.setTimeSpec(Qt::UTC);

    // Top Level Tree Items
    Advisory = new QTreeWidgetItem();
    Caution = new QTreeWidgetItem();
    Warning = new QTreeWidgetItem();
    Error = new QTreeWidgetItem();

    // Set font for top-level items
    Advisory->setFont(0, QFont("Serif", 20));
    Caution->setFont(0, QFont("Serif", 20));
    Warning->setFont(0, QFont("Serif", 20));

    // Set severity parents' text
    Advisory->setText(0, QString("Advisory"));
    Caution->setText(0, QString("Caution"));
    Warning->setText(0, QString("Warning"));

    // Set top-level items' background colors for aesthetic
    Advisory->setBackgroundColor(0, QColor(137,255,196, 200));
    Caution->setBackgroundColor(0, QColor(255,255,136, 200));
    Warning->setBackgroundColor(0, QColor(255,135,135, 200));

    // Append to a list of top level items
    topLevelList.append(Advisory);
    topLevelList.append(Caution);
    topLevelList.append(Warning);
}

Graph::~Graph()
{
    topLevelList.clear();

    gridLineX.clear();
    gridLineY.clear();

    events.clear();

    rows.clear();
}

// Struct constructors
Graph::EventItem::EventItem(std::vector<QGraphicsEllipseItem*> gin, BC_Event *eventin)
{
    for(QGraphicsEllipseItem* g:gin) graphicsItems.push_back(g);
    event = eventin;
    unboundedEventArrow = new QGraphicsPixmapItem;
    treeItem = new BC_DITL_SEVTREE_ITEM;
}

Graph::EventItem::EventItem(std::vector<QGraphicsRectItem*> gin, Graph::EventItem::RectType typein, BC_Event *eventin)
{
    for(QGraphicsRectItem* g:gin) graphicsItems.push_back(g);
    type = typein;
    event = eventin;
    unboundedEventArrow = new QGraphicsPixmapItem;
    treeItem = new BC_DITL_SEVTREE_ITEM;
}

Graph::EventItem::EventItem(std::vector<QGraphicsRectItem*> gin, Graph::EventItem::RectType typein, BC_Event peventsin, BC_Event* peventfin)
{
    for(QGraphicsRectItem* g:gin) graphicsItems.push_back(g);
    type = typein;

    event = new BC_Event;
    event->message="NULL EVENT (Maybe referencing a paired event?)";
    event->filename="NULL EVENT (Maybe referencing a paired event?)";

    pevents = peventsin;
    peventf = peventfin;
    unboundedEventArrow = new QGraphicsPixmapItem;
    treeItem = new BC_DITL_SEVTREE_ITEM;
}

Graph::Row::Row(std::string namein, double yin){
    name = namein;
    y = yin;
}

Graph::EventItem::~EventItem()
{
    delete unboundedEventArrow;
    delete treeItem->child;
    delete treeItem->item;
    delete treeItem;
}

void Graph::addTreeItem(BC_DITL_SEVTREE_ITEM* item, Graph::EventItem* event)
    // Adds an item (singluar) to the event tree
{
    event->treeItem = item;
    // Add the item (and thus its children) to the correct top-level severity category
    if(event->treeItem->sev==BC_Event::Severity::ADVISORY)
    {
        Advisory->addChild(event->treeItem->item);
        Advisory->setText(0, QString("Advisory (").append(QString::number(Advisory->childCount())).append(")"));
    } else

    if(event->treeItem->sev==BC_Event::Severity::CAUTION)
    {
        Caution->addChild(event->treeItem->item);
        Caution->setText(0, QString("Caution (").append(QString::number(Caution->childCount())).append(")"));
    } else

    if(event->treeItem->sev==BC_Event::Severity::WARNING)
    {
        Warning->addChild(event->treeItem->item);
        Warning->setText(0, QString("Warning (").append(QString::number(Warning->childCount())).append(")"));
    }
}
