#ifndef BC_BULLETIN_H
#define BC_BULLETIN_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QString>
#include <QRegExp>
#include <QDebug>
#include <QColor>
#include <QDateTime>
#include <QScrollBar>
#include <QIcon>
#include <QTimer>
#include <algorithm>
#include <QMessageBox>
#include <QCloseEvent>

#include "item.h"
#include "fswitem.h"
#include "sorting.h"

#include "../modules/BARCoMmS_CFDP/barcomms_cfdp.h"

#include "../dependencies/net/UDPConnection.h"
#include "../dependencies/net/PDU.h"

#include "../dependencies/trek/CCSDSTelemetryHeader.h"
#include "../dependencies/trek/telemetry/HealthStatus_Telemetry.h"

namespace Ui {
class BC_Bulletin;
}

class BC_Bulletin : public QMainWindow
{
    Q_OBJECT

public:

    explicit BC_Bulletin(QWidget *parent = 0);
    ~BC_Bulletin();

    //Removes items from the tree designated by user so sorting can take place
    void removeItems(int tree);

    //Replaces items from the tree desginated by user after sorting takes place
    void replaceItems(int tree);

    //Displays informative window (exit)
    void closeEvent(QCloseEvent*);

    //Stores the last transaction number referenced by CFDP
    QString lastNum;

    //Stores items in CFDP tree so they can be accessed easily from BC_Bulletin
    QList<Item> treeItems;

    //Stores items in FSW tree so they can be accessed easily from BC_Bulletin
    QList<FSWItem*> fswTreeItems;

    /*Tree items are colored to indicate status of transaction or command
     * For CFDP: Red    = transaction abandoned
     *           Orange = transaction cancelled (or cancelling), fault
     *           Yellow = timer expired, NAK received/sent
     *           Green  = transaction completed successfully
     *           None   = transaction in (normal) progress
     *
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

    /*Top level items are flagged to indicate temporary status of transaction or command
     * For CFDP: Orange = Child is orange indicating cancel or fault
     *           Yellow = Child is yellow indicating timer expiration or NAK
     *           Empty  = transaction in (normal) progress
     *
     * For FSW:  Not currently used
    */
    QIcon orangeIcon = QIcon("resources/Orange_flag.png");
    QIcon yellowIcon = QIcon("resources/Yellow_flag.png");
    QIcon empty = QIcon();

    //Text colors for tree items
    QColor white = QColor(205, 201, 201);
    QColor black = QColor(0, 0, 0);

    //Dialog window to sort tree items according to user input
    Sorting *sorting;

    //Informative dialog window to inform user they are exiting the program
    QMessageBox *msgExit;

public slots:

    //Slot will parse CFDP command line output and display relevant information
    void takeCFDP(char *str);

    //Slot will display relevant information from command packets originating within application
    void takeFSW(int apid, int id);

    //Slot will parse telemetry from FSW (health and status packets) and display status of commands
    void pduReceived(ByteBuffer);

    //Search function, slot searches tree items for user input and highlights all matches
    void goTo();

    //Erase messages in search bar
    void eraseSearchBar();

    //Toggle to expand/collapse item and its children
    void expandCollapseItem();

    //Toggle to expand/collapse all items
    void expandCollapseAll();

    //Toggle to automatically scroll to bottom of tree when new item is added
    void autoScroll();

    //Toggle to automatically expand all items when new item is added
    void autoExpand();

    //Opens dialog window to sort tree items
    void openSorting();

    //Sorts tree items according to user input (chronological order, file size, command, or status)
    void sortItems(int sortOption);

signals:

    //Emitted when a health and status packet is received, displays the received signal strength in the command window
    void rssi(int);

    /*Emitted when an item (including children and grandchildren) is added to either tree,
     * connects to autoScroll and autoExpand functions
    */
    void itemAdded();

    //Emitted when Bulletin window is closed, tells Packet Listener Thread that it is no longer being used
    void dying();

private:
    Ui::BC_Bulletin *ui;

};


#endif // BC_BULLETIN_H
