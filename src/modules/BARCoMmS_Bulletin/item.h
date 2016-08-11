#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDateTime>

class Item
{
public:

    //Adds new item (new transaction) to CFDP tree
    Item(QString transNum, QString classNum, QString name, QString size, float sizeFloat, QString node);

    //Adds child to item in CFDP tree
    int addChild(int column, QColor color, QString text, QIcon icon);

    //Adds grandchild to item in CFDP tree
    void addGrandChild(int parent, int column, QString text);

    //Generates and returns UTC timestamp as string
    QString time();

    /*Stores CFDP transaction number, file name, time transaction was initiated,
     * and file size so they can be easily accessed from BC_Bulletin
     */
    QString treeNum;
    QString fileName;
    QDateTime startTime;
    float fileSize;

    /*Marks current status of CFDP transaction so items can be easily sorted in BC_Bulletin
     *     0 = successfully completed
     *     1 = abandoned
     *     2 = cancelled
     *     3 = flagged Orange (fault occured, cancellation in progress)
     *     4 = flaggeed Yellow (timer expired, NAK received/sent)
     *     5 = in (normal) progress)
     */
    int status;

    //Top level item representing one CFDP transaction
    QTreeWidgetItem *topLevelItem = new QTreeWidgetItem();

    //First child of top level item, contains details immediately available about transaction
    QTreeWidgetItem *details = new QTreeWidgetItem();

    //Children of details, contain time initiated, transaction number, transaction class, file name, file size, and node
    QTreeWidgetItem *timeChild = new QTreeWidgetItem();
    QTreeWidgetItem *transChild = new QTreeWidgetItem();
    QTreeWidgetItem *classChild = new QTreeWidgetItem();
    QTreeWidgetItem *nameChild = new QTreeWidgetItem();
    QTreeWidgetItem *sizeChild = new QTreeWidgetItem();
    QTreeWidgetItem *nodeChild = new QTreeWidgetItem();

    /*Tree items are colored to indicate status of transaction
     * For CFDP: Red    = transaction abandoned
     *           Orange = transaction cancelled (or cancelling), fault
     *           Yellow = timer expired, NAK received/sent
     *           Green  = transaction completed successfully
     *           None   = transaction in (normal) progress
     */
    QColor red  = QColor(255, 85, 85, 160);
    QColor orange = QColor(255, 154, 53, 145);
    QColor yellow = QColor(255, 255, 102, 168);
    QColor green = QColor(147, 249, 117, 172);
    QColor none = QColor(30, 30, 30);

    //Text colors for tree items
    QColor white = QColor(205, 201, 201);
    QColor black = QColor(0, 0, 0);

    //Stores all children of the top level item for easy access later
    QList<QTreeWidgetItem*> children;
};

//Sort tree items by file size (smallest first)
struct sortBySize
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return (start.fileSize < end.fileSize);
    }
};

//Sort tree items by file size (largest first)
struct sortBySize2
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return (start.fileSize > end.fileSize);
    }
};

//Sort tree items in chronoloical order (oldest first)
struct sortByTimeCFDP
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return(start.startTime < end.startTime);
    }
};

//Sort tree items in chronological order (newest first)
struct sortByTimeCFDP2
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return(start.startTime > end.startTime);
    }
};

//Sort tree items by status (Successful, unsuccessful, in progress)
struct sortByStatusCFDP
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return(start.status < end.status);
    }
};

//Sort tree items by status (In progress, unsuccessful, successful)
struct sortByStatusCFDP2
{
    inline bool operator() (const Item& start, const Item& end)
    {
        return(start.status > end.status);
    }
};

#endif // ITEM_H
