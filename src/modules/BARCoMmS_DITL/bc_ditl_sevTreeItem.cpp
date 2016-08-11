#include "bc_ditl_sevTreeItem.h"
#include "bc_ditl_constants.cpp"

void BC_DITL_SEVTREE_ITEM::clean()
{
    item->removeChild(child);
    delete item;
}

BC_DITL_SEVTREE_ITEM::BC_DITL_SEVTREE_ITEM()
{
    details = NULL_ITEM;
}

BC_DITL_SEVTREE_ITEM::BC_DITL_SEVTREE_ITEM(BC_Event::Severity sev_in, std::string name_in, std::string det_in, double x_in, double y_in, double w_in, double h_in, bool isPoint_in)
{
    sev = sev_in;
    name = name_in;
    details = det_in;
    x = x_in;
    y = y_in;
    w = w_in;
    h = h_in;
    isPoint = isPoint_in;

    while(details.size()!=0)
    {
        if(details.front()!='(') details.erase(details.begin());
        else break;
    }

    child = new QTreeWidgetItem();
    item = new QTreeWidgetItem();

    details = QString::fromStdString(details).replace(" GMT", "\0").toStdString();

    item->setText(0, QString::fromStdString(name));
    item->setFont(0, QFont("Serif", 15));
    item->setTextColor(0,QColor(205,201,201));
    child->setText(0, QString::fromStdString(details));
    child->setTextColor(0,QColor(205,201,201));
    item->addChild(child);
}
