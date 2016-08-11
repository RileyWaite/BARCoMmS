#ifndef BC_DITL_SEVTREE_H
#define BC_DITL_SEVTREE_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QString>
#include <QLabel>
#include <QList>

#include <string>

#include "../dependencies/bc_Event.h"

class BC_DITL_SEVTREE_ITEM
{
public:
    BC_DITL_SEVTREE_ITEM();
    BC_DITL_SEVTREE_ITEM(BC_Event::Severity, std::string, std::string, double, double, double, double, bool);

    BC_Event::Severity sev;
    QTreeWidgetItem *child;
    QTreeWidgetItem *item;
    std::string details;
    std::string name;
    double x,y,w,h;
    bool isPoint;

    void clean();
};

#endif // BC_DITL_SEVTREE_H
