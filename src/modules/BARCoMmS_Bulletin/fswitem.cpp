#include "fswitem.h"

//Adds new item (new command) to FSW tree and starts timers which flag item if no response is heard from FSW
FSWItem::FSWItem(int apid, int id)
{
    //Stores APID, unique ID, and time command was sent so they can be easily accessed from BC_Bulletin
    command = apid;
    fswTreeNum = id;
    startTime = QDateTime::currentDateTimeUtc();

    //Sets text of top level item based on command APID
    QString str;
    if(apid == 1) str = "1     FSW Command";
    else if(apid == 2) str = "2     Ping";
    else if(apid == 3) str = "3     Downlink Buffer";
    else if(apid == 4) str = "4     Comm Schedule";
    else if(apid == 5) str = "5     Telem Query";
    else if(apid == 6) str = "6     GNC";
    else if(apid == 7) str = "7     Decom Commit";
    else if(apid == 8) str = "8     Camera Download Images";        //switched with decom enable 14
    else if(apid == 9) str = "9     Prop Schedule";
    else if(apid == 10) str = "10   Safe Mode";
    else if(apid == 11) str = "11   Oper Mmode";
    else if(apid == 12) str = "12   Abort Comm Pass";
    else if(apid == 13) str = "13   Camera Capture Image";
    else if(apid == 14) str = "14   Decom Enable";
    else if(apid == 15) str = "15   Set Dev Avail";
    else if(apid == 16) str = "16   Set Dev Power";
    else if(apid == 17) str = "17   Reset Dev";
    else if(apid == 18) str = "18   FSW Restart";
    else if(apid == 19) str = "19   FSW Reboot";
    else if(apid == 20) str = "20   Transmit Data Rate";
    else if(apid == 21) str = "21   Event Retrans";
    else qDebug() << "apid not found";

    topLevelItem->setText(0, str + "\n");
    topLevelItem->setTextColor(0, white);

    //Sets up item containing unique sequence ID (child of top level item)
    cmdSeqId->setText(0, "ID: " + QString::number(id));
    cmdSeqId->setTextColor(0, white);
    topLevelItem->addChild(cmdSeqId);
    children.push_back(cmdSeqId);

    //Sets up item containing timestamp (child of top level item)
    time->setText(0, "Time initiated: " + startTime.toString());
    time->setTextColor(0, white);
    topLevelItem->addChild(time);
    children.push_back(time);

    //Initiates first timer which, after expiration, colors item yellow
    timer1->setSingleShot(true);
    connect(timer1, SIGNAL(timeout()), this, SLOT(flagYellow()));
    timer1->start(timer1Length);

    //Initiates second timer which, after expiration, colors item orange
    timer2->setSingleShot(true);
    connect(timer2, SIGNAL(timeout()), this, SLOT(flagOrange()));
    timer2->start(timer2Length);

    //Initiates third timer which, after expiration, colors item red
    timer3->setSingleShot(true);
    connect(timer3, SIGNAL(timeout()), this, SLOT(flagRed()));
    timer3->start(timer3Length);

    //Sets current status of transaction to be in progress
    status = 4;

    //Sets current state of transaction to be unfinished
    finished = 0;
}

//Adds child to item in FSW tree
void FSWItem::addChild(QColor color, QString text, QColor topColor)
{
    //Creates and sets up child
    QTreeWidgetItem *newChild = new QTreeWidgetItem();
    newChild->setText(0, text);
    newChild->setBackgroundColor(0, color);

    //Sets text color (for easy viewing) based on color given to child
    if(color != none) newChild->setTextColor(0, black);
    else newChild->setTextColor(0, white);

    //Sets top level item color
    topLevelItem->setBackgroundColor(0, topColor);

    //Sets text color (for easy viewing) of top level item based on color given to top level item
    if(topColor != none) topLevelItem->setTextColor(0, black);
    else topLevelItem->setTextColor(0, white);

    //Adds child to top level item
    topLevelItem->addChild(newChild);
    children.push_back(newChild);

    //If FSW has responded to command
    if(finished == 1)
    {
        //Stores time FSW responded
        finishedTime = QDateTime::currentDateTimeUtc();
        elapsedTime = (finishedTime.toTime_t() - startTime.toTime_t());

        //Creates and sets up child containing the time FSW responded
        QTreeWidgetItem *timeChild = new QTreeWidgetItem();
        timeChild->setText(0, "Time of response: " + finishedTime.toString());
        timeChild->setTextColor(0, white);
        topLevelItem->addChild(timeChild);

        //Creates and sets up child containing elapsed time for command to be sent and responded to
        QTreeWidgetItem *timeElapsedChild = new QTreeWidgetItem();
        timeElapsedChild->setText(0, "Elapsed time: " + QString::number(elapsedTime) + " seconds");
        timeElapsedChild->setTextColor(0, white);
        topLevelItem->addChild(timeElapsedChild);
    }
}

//Disconnects timers which flag item if FSW responds to command
void FSWItem::disconnectTimers()
{
    disconnect(timer1, SIGNAL(timeout()), this, SLOT(flagYellow()));
    disconnect(timer2, SIGNAL(timeout()), this, SLOT(flagOrange()));
    disconnect(timer3, SIGNAL(timeout()), this, SLOT(flagRed()));
}

//Colors the top level item yellow after first timer expires, adds child item with message
void FSWItem::flagYellow()
{
    addChild(yellow, "Command has not been acknowledged in " + timer1Label, yellow);
    status = 3;
}

//Colors the top level item orange after second timer expires, adds child item with message
void FSWItem::flagOrange()
{
    addChild(orange, "Command has not been acknowledged in " + timer2Label, orange);
    status = 2;
}

//Colors the top level item red after third timer expires, adds child item with message
void FSWItem::flagRed()
{
    addChild(red, "Command has not been acknowledged in " + timer3Label, red);
    status = 1;
}
