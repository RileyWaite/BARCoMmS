#ifndef FSWITEM_H
#define FSWITEM_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

class FSWItem : public QTimer
{
    Q_OBJECT

public:

    //Adds new item (new command) to FSW tree and starts timers which flag item if no response is heard from FSW
    FSWItem(int apid, int id);

    virtual ~FSWItem() {}

    //Adds child to item in FSW tree
    void addChild(QColor color, QString text, QColor topColor);

    //Disconnects timers which flag item if FSW responds to command
    void disconnectTimers();

    //Stores APID, unique ID, and time command was sent so they can be easily accessed from BC_Bulletin
    int command;
    int fswTreeNum;
    QDateTime startTime, finishedTime;
    int elapsedTime;

    /*Marks current status of FSW command so items can be easily sorted in BC_Bulletin
     *     0 = ACK from FSW
     *     1 = NAK from FSW, no response in 10 (confirgurable) minutes
     *     2 = no response in 5 (configurable) minutes
     *     3 = no response in 3 (configurable) minutes
     *     4 = in (normal) progress
     */
    int status;

    //Marks current state of FSW command (finished or unfinished), once finished ignore further ACKS from FSW
    bool finished;

    //Top level item representing one command
    QTreeWidgetItem *topLevelItem = new QTreeWidgetItem();

    //Children of top level item, contain unique ID for command and time command was sent
    QTreeWidgetItem *cmdSeqId = new QTreeWidgetItem();
    QTreeWidgetItem *time = new QTreeWidgetItem();

    /*Tree items are colored to indicate status of command
    * For FSW:  Red    = received NAK from FSW, no response in 10 (configurable) minutes
    *           Orange = no response in 5 (configurable) minutes
    *           Yellow = no response in 3 (configurable) minutes
    *           Green  = received ACK from FSW
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
    
    //Timers which, after expiration, change color of item to indicate status of command
    QTimer *timer1 = new QTimer();
    QTimer *timer2 = new QTimer();
    QTimer *timer3 = new QTimer();

    /*Change these values if you want to change length of timers
    * Ints are length of timer in milliseconds
    * Strings are simply for display in the tree
    */
    int timer1Length = 5000;
    int timer2Length = 10000;
    int timer3Length = 15000;
    QString timer1Label = "5 seconds";
    QString timer2Label = "10 seconds";
    QString timer3Label = "15+ seconds";

public slots:

    //Colors item yellow after 3 minutes
    void flagYellow();

    //Colors item orange after 5 minutes
    void flagOrange();

    //Colors item red after 10 minutes
    void flagRed();
};

//Sort tree items in chronoloical order (oldest first)
struct sortByTimeFSW
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->startTime < end->startTime);
    }
};

//Sort tree items in chronological order (newest first)
struct sortByTimeFSW2
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->startTime > end->startTime);
    }
};

//Sort tree items by command (lowest APID first)
struct sortByCommand
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->command < end->command);
    }
};

//Sort tree items by command (highest APID first)
struct sortByCommand2
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->command > end->command);
    }
};

//Sort tree items by status (Successful, unsuccessful, in progress)
struct sortByStatusFSW
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->status < end->status);
    }
};

//Sort tree items by status (In progress, unsuccessful, successful)
struct sortByStatusFSW2
{
    inline bool operator() (FSWItem *start, FSWItem *end)
    {
        return(start->status > end->status);
    }
};

#endif // FSWITEM_H
