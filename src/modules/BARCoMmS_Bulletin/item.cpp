#include "item.h"

//Adds new item (new transaction) to CFDP tree
Item::Item(QString transNum, QString classNum, QString name, QString size, float sizeFloat, QString node)
{
    /*Stores CFDP transaction number, file name, file size, and time transaction was initiated
     * so they can be easily accessed from BC_Bulletin
     */
    treeNum = transNum;
    fileName = name;
    fileSize = sizeFloat;
    startTime = QDateTime::currentDateTimeUtc();

    //Shortens file name for neater display
    QString text;
    QString str = name;
    QStringList strList = str.split('/');
    QStringList strList2, strList3;
    if(strList.back().size() > 24)
    {
        strList2 = strList.back().split('.');

        if(strList2[0].size() > 22)
        {
            strList2[0].insert(22, " ");
            strList3 = strList2[0].split(' ');
            text = "Transaction " + transNum + "\n" + size.leftJustified(12, ' ') + "  ...'" + strList3[0] + "..." + strList2[1] + "\n";
        }
        else text = "Transaction " + transNum + "\n" + size.leftJustified(12, ' ') + "  ...'" + strList2[0] + "." + strList2[1] + "\n";
    }
    else text = "Transaction " + transNum + "\n" + size.leftJustified(12, ' ') + "  ...'" + strList.back() + "\n";

    //Sets text and text color of top level item
    topLevelItem->setText(0, text);
    topLevelItem->setText(1, text);
    topLevelItem->setTextColor(0, white);
    topLevelItem->setTextColor(1, white);

    //Sets up item containing transaction details (child of top level item)
    details->setText(0, "Transaction details");
    details->setText(1, "      Transaction details");
    details->setTextColor(0, white);
    details->setTextColor(1, white);
    topLevelItem->addChild(details);
    children.push_back(details);

    //Sets up item containing timestamp (child of details)
    timeChild->setText(0, "Time initiated: " + time());
    timeChild->setText(1, "            Time initiated: " + time());
    timeChild->setTextColor(0, white);
    timeChild->setTextColor(1, white);
    details->addChild(timeChild);

    //Sets up item containing transaction number (child of details)
    transChild->setText(0, "Transaction number: " + transNum);
    transChild->setText(1, "            Transaction number: " + transNum);
    transChild->setTextColor(0, white);
    transChild->setTextColor(1, white);
    details->addChild(transChild);

    //Sets up item containing transaction class (child of details)
    if(classNum.contains("1")) classNum = "Unreliable (1)";
    else if(classNum.contains("2")) classNum = "Reliable (2)";
    else classNum = "Unknown";
    classChild->setText(0, "Class type: " + classNum);
    classChild->setText(1, "            Class type: " + classNum);
    classChild->setTextColor(0, white);
    classChild->setTextColor(1, white);
    details->addChild(classChild);

    //Sets up item containing full file name (child of details)
    name.insert(40, " ");
    name.insert(83, " ");
    QStringList nameList = name.split(' ');
    if(nameList[2].size() > 0)
    {
        nameChild->setText(0, "File name: " + nameList[0] + "\n   " + nameList[1] + "\n   " + nameList[2]);
        nameChild->setText(1, "            File name: " + nameList[0] + "\n               " + nameList[1] + "\n               " + nameList[2]);
    }
    else
    {
        nameChild->setText(0, "File name: " + nameList[0] + "\n   " + nameList[1]);
        nameChild->setText(1, "            File name: " + nameList[0] + "\n               " + nameList[1]);
    }
    nameChild->setTextColor(0, white);
    nameChild->setTextColor(1, white);
    details->addChild(nameChild);

    //Sets up item containing file size (child of details)
    sizeChild->setText(0, "File size: " + size);
    sizeChild->setText(1, "            File size: " + size);
    sizeChild->setTextColor(0, white);
    sizeChild->setTextColor(1, white);
    details->addChild(sizeChild);

    //Sets up item containing node (child of details)
    if(!node.contains("N/A"))
    {
        nodeChild->setText(0, "Receiving node: " + node);
        nodeChild->setText(1, "            Receiving node: " + node);
        nodeChild->setTextColor(0, white);
        nodeChild->setTextColor(1, white);
        details->addChild(nodeChild);
    }

    //Sets current status of transaction to be in progress
    status = 5;
}

//Adds child to item in CFDP tree
int Item::addChild(int column, QColor color, QString text, QIcon icon)
{
    //Creates child
    QTreeWidgetItem *newChild = new QTreeWidgetItem();

    //Creates item for timestamp, to become first child of child
    QTreeWidgetItem *timeChild = new QTreeWidgetItem();

    //Sets up child and timestamp based on parameters given to child
    if(column == 0)
    {
        newChild->setText(0, text);
        newChild->setBackgroundColor(0, color);
        timeChild->setText(0, time());
        timeChild->setTextColor(0, white);
    }
    else if(column == 1)
    {
        newChild->setText(1, "      " + text);
        newChild->setBackgroundColor(1, color);
        timeChild->setText(1, "            " + time());
        timeChild->setTextColor(1, white);
    }
    else
    {
        newChild->setText(0, text);
        newChild->setText(1, "      " + text);
        newChild->setBackgroundColor(0, color);
        newChild->setBackgroundColor(1, color);
        timeChild->setText(0, time());
        timeChild->setText(1, "            " + time());
        timeChild->setTextColor(0, white);
        timeChild->setTextColor(1, white);
    }

    //Sets text color (for easy viewing) and status (for easy sorting) based on color given to child
    if(color == yellow)
    {
        newChild->setTextColor(0, black);
        newChild->setTextColor(1, black);
        status = 4;
    }
    else if(color == orange)
    {
        newChild->setTextColor(0, black);
        newChild->setTextColor(1, black);
        status = 3;
    }
    else if(color == none)
    {
        newChild->setTextColor(0, white);
        newChild->setTextColor(1, white);
        status = 5;
    }
    else
    {
        newChild->setTextColor(0, black);
        newChild->setTextColor(1, black);
    }

    //Sets top level item icon
    topLevelItem->setIcon(0, icon);
    topLevelItem->setIcon(1, icon);

    //Adds child and timestamp to top level item
    topLevelItem->addChild(newChild);
    children.push_back(newChild);
    newChild->addChild(timeChild);

    //Returns current number of children for easy access when adding grandchildren
    return(children.size());
}

//Adds grandchild to item in CFDP tree
void Item::addGrandChild(int parent, int column, QString text)
{
    //Creates grandchild
    QTreeWidgetItem *newGrandchild = new QTreeWidgetItem();

    //Sets up grandchild based on parameters given to grandchild
    if(column == 0)
    {
        newGrandchild->setText(0, text);
        newGrandchild->setTextColor(0, white);
    }
    else if(column == 1)
    {
        newGrandchild->setText(1, "            " + text);
        newGrandchild->setTextColor(1, white);
    }
    else
    {
        newGrandchild->setText(0, text);
        newGrandchild->setText(1, "            " + text);
        newGrandchild->setTextColor(0, white);
        newGrandchild->setTextColor(1, white);
    }

    //Adds grandchild to its parent (child of top level item)
    children[parent]->addChild(newGrandchild);
}

//Generates and returns UTC timestamp as string
QString Item::time()
{
    return("(UTC) " + QDateTime::currentDateTimeUtc().toString());
}
