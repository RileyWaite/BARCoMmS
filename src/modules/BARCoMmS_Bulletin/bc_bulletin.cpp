#include "bc_bulletin.h"
#include "ui_bc_bulletin.h"

BC_Bulletin::BC_Bulletin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BC_Bulletin)
{
    ui->setupUi(this);

    //Set size of main window
    this->setFixedSize(1220, 521);

    //Setting up CFDP Transfer and Receive windows
    ui->tx->setColumnCount(2);
    ui->tx->setColumnWidth(0, 405);
    ui->tx->setColumnWidth(1, 300);

    QStringList headerLabels;
    headerLabels << "Transfer Window" << "Received Window";
    ui->tx->setHeaderLabels(headerLabels);

    ui->tx->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //Setting up FSW Command display window
    ui->fsw->setColumnCount(1);
    ui->fsw->setHeaderLabel("FSW Command Window");
    ui->fsw->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //Add BARCoMmS logo
    QPixmap pixmap("resources/BC_Green.png");
    ui->logo->setPixmap(pixmap);

    //Set the window icon
    setWindowIcon(QIcon("resources/BC_Logo.png"));

    //Toggle to expand selected item and its children
    ui->pushButton->setText("Expand/Collapse Item");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(expandCollapseItem()));

    //Toggle to expand all items
    ui->pushButton_2->setText("Expand/Collapse All");
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(expandCollapseAll()));

    //Toggle to scroll to bottom of tree when new item is added
    ui->pushButton_3->setText("Toggle Auto-Scroll");
    ui->pushButton_3->setCheckable(true);
    ui->pushButton_3->setChecked(false);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(autoScroll()));

    //Toggle to automatically expand items when new item is added
    ui->pushButton_4->setText("Toggle Auto-Expand");
    ui->pushButton_4->setCheckable(true);
    ui->pushButton_4->setChecked(false);
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(autoExpand()));

    //Open window to choose sort order
    ui->pushButton_5->setText("Sorting Options");
    sorting = new Sorting(this);
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(openSorting()));
    connect(sorting, SIGNAL(chosen(int)), this, SLOT(sortItems(int)));

    //Search function
    ui->progressBar->setVisible(false);
    connect(ui->searchBar, SIGNAL(returnPressed()), this, SLOT(goTo()));

}

BC_Bulletin::~BC_Bulletin()
{
    delete ui;
}

//Displays informative window (Exit)
void BC_Bulletin::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit\nBARCoMmS Bulletin?",
                                                                QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        //Signal to BC_PacketListenerThread to tell it that a use has died
        emit dying();
        event->accept();
    }
    else event->ignore();
}

//Slot will display relevant information from command packets originating within application
void BC_Bulletin::takeFSW(int apid, int id)
{
    //Add new item to fsw tree
    FSWItem *item = new FSWItem(apid, id);
    fswTreeItems.push_back(item);
    ui->fsw->addTopLevelItem(fswTreeItems.back()->topLevelItem);
    emit itemAdded();
}

//Slot will parse telemetry (health and status packets) and display status of commands
void BC_Bulletin::pduReceived(ByteBuffer buf)
{
    bool found = 0;

    //Deserialize packet header and extract apid
//    isat_trek::CCSDSTelemetryHeader hdr;
//    hdr.fromBytes(buf);

//    qDebug() << hdr.apid;
    int apid;
    buf.getBits(0, 32, apid);

    //Make sure packet is health and status
    if(apid == 1)
    {
        //Deserialize health and status packet
        isat_trek::HealthStatus_Telemetry hs;
        hs.fromBytes(buf);

        //Extract received signal strength from health and status packet, send to Command for display
        emit(rssi(hs.receivedSigStr));

        //Match last command ID received by FSW to command sent by ground
        for(unsigned short i = 0; i < fswTreeItems.size(); ++i)
        {
            if(hs.lastCommand == fswTreeItems[i]->fswTreeNum)
            {
                //Disconnect timers which flag commands if there is no response from FSW
                fswTreeItems[i]->disconnectTimers();

                //If status is ACK, mark command as complete
                if(hs.commandStatus == 1)
                {
                    if(fswTreeItems[i]->finished) {found = 1; break;}
                    else
                    {
                        fswTreeItems[i]->finished = 1;
                        fswTreeItems[i]->addChild(green, "Received ACK", green);
                        fswTreeItems[i]->status = 0;
                    }
                }

                //If status is NAK, mark command as incomplete/failed
                else if (hs.commandStatus == 0)
                {
                    if(fswTreeItems[i]->finished) {found = 1; break;}
                    else
                    {
                        fswTreeItems[i]->finished = 1;
                        fswTreeItems[i]->addChild(red, "FSW NAK", red);
                        fswTreeItems[i]->status = 1;
                    }
                }
            }

            emit itemAdded();
            found = 1;
        }
    }
}

//Slot will parse CFDP command line output and display relevant information
void BC_Bulletin::takeCFDP(char* str)
{
    //Convert char* from command window to QString
    QString input = str;

    //Regular expressions for receive (vs send)
    QRegExp recvExp("(---->)");
    QRegExp otherRecvExp("Recv");
    int column; QString text;

    //Regular expressions for transaction ID, freeze and thaw commands
    QRegExp transNumExp("[0-9]{2,6}[_][0-9]{1,10}");
    QRegExp freezeExp("(freeze)");
    QRegExp thawExp("(thaw)");

    //Regular expressions for information found in message classes
    QRegExp memUseExp("(nak)[_](mem)[:][ ][ ][a-zA-Z0-9 #.]*");
    QRegExp rawPDUExp("(Pdu)[ ][(](raw)[)][:][ ][ ][ 0-9a-zA-Z]+");
    QRegExp gapExp("(Gap added)");
    QRegExp rangeExp("(Removing range)");
    QRegExp validExp("(Valid_filedata_received: )[0-9]*[-][0-9]*");

    //Regular expression for CFDP engine message
    QRegExp cfdpEngineExp("(cfdp_engine: )[a-zA-Z0-9 <>,./\?;:'()-_]*");

    //If input contains transaction number
    if(transNumExp.indexIn(input) != -1)
    {
        //Store transaction number as QString transNum
        QString transNum = transNumExp.cap(0);
        bool found = 0;

        //Match transaction number from new input to transaction already displayed on tree
        for(unsigned short i = 0; i < treeItems.size(); ++i)
        {
        //If transaction has already begun,
        if(transNum == treeItems[i].treeNum)
        {
            //Display transaction initiated
            QRegExp startedExp("((Transaction)[ ][0-9]{2,6}[_][0-9]{1,10}[ ](started)[ ][(](sending))");
            if(startedExp.indexIn(input) != -1) treeItems[i].addChild(0, none, "Transaction " + transNum + " initiated", empty);

            //Display metadata sent
            QRegExp metadataExp("(MD)[_](Sent)");
            if(metadataExp.indexIn(input) != -1) treeItems[i].addChild(0, none, "Metadata sent", empty);

            //Display message if empty file is sent
            if(input.contains("unbounded file"))
            {
                treeItems[i].addChild(0, red, "Empty file sent", empty);
                treeItems[i].topLevelItem->setBackgroundColor(0, red);
                treeItems[i].topLevelItem->setBackgroundColor(1, red);
                treeItems[i].topLevelItem->setTextColor(0, black);
                treeItems[i].topLevelItem->setTextColor(1, black);
                treeItems[i].status = 1;
            }

            //Display PDU prepared
            QRegExp fdPduExp("(Pdu: FD)");
            if(fdPduExp.indexIn(input) != -1)
            {
                int k = treeItems[i].addChild(0, none, "PDU", empty);

                //Display offset of PDU in entire file
                QString offset;
                QRegExp offsetExp("(offset)[=][0-9]*");
                if(offsetExp.indexIn(input) != -1)
                {
                    QString offsetString = offsetExp.cap(0);
                    QStringList offsetList = offsetString.split('=');
                    offset = offsetList[1];

                    treeItems[i].addGrandChild(k - 1, 0, "Offset: " + offset + " bytes");
                }

                //Display total file length
                QString length;
                QRegExp lengthExp("(length)[=][0-9]*");
                if(lengthExp.indexIn(input) != -1)
                {
                    QString lengthString = lengthExp.cap(0);
                    QStringList lengthList = lengthString.split('=');
                    length = lengthList[1];

                    treeItems[i].addGrandChild(k - 1, 0, "Length: " + length + " bytes");
                }

                //Display acked?
                QString thing;
                QRegExp thingExp("[(][a-zA-Z ]*[,][ ][A-Z]*[-][>][A-Z]*[,][ ][a-zA-Z ]*[)]");
                if(thingExp.indexIn(input) != -1)
                {
                    thing = thingExp.cap(0);

                    treeItems[i].addGrandChild(k - 1, 0, thing);
                }
            }

            //Display file segment sent/received
            QRegExp fileSegRecvExp("(File_Segment_)");
            if(fileSegRecvExp.indexIn(input) != -1)
            {
                if(otherRecvExp.indexIn(input) != -1) {column = 1; text = "File segment received";}
                else {column = 0; text = "File segment sent";}

                int k = treeItems[i].addChild(column, none, text, empty);

                //Display offset of PDU in entire file
                QString offset;
                QRegExp offsetExp("(offset)[=][0-9]*");
                if(offsetExp.indexIn(input) != -1)
                {
                    QString offsetString = offsetExp.cap(0);
                    QStringList offsetList = offsetString.split('=');
                    offset = offsetList[1];

                    treeItems[i].addGrandChild(k - 1, column, "Offset: " + offset + " bytes");
                }

                //Display total file length
                QString length;
                QRegExp lengthExp("(length)[=][0-9]*");
                if(lengthExp.indexIn(input) != -1)
                {
                    QString lengthString = lengthExp.cap(0);
                    QStringList lengthList = lengthString.split('=');
                    length = lengthList[1];

                    treeItems[i].addGrandChild(k - 1, column, "Length: " + lengthList[1] + " bytes");
                }
            }

            //Display EOF sent/received
            QRegExp eofExp("(EOF)[:][ ](xsum)[=][a-zA-Z0-9]*[,][ ](file)[-](size)[=][0-9]*");
            if(eofExp.indexIn(input) != -1)
            {
                if(recvExp.indexIn(input) != -1) {column = 1; text = "EOF received";}
                else {column = 0; text = "EOF sent";}

                int k = treeItems[i].addChild(column, none, text, empty);

                //Display file checksum
                QString xsumString = eofExp.cap(0);
                QStringList xsumList = xsumString.split(':');
                QStringList xsumList2 = xsumList[1].split(',');
                QStringList xsumList3 = xsumList2[0].split('=');
                treeItems[i].addGrandChild(k - 1, column, "File checksum: " + xsumList3[1]);

                //Display file size
                QString putSize;
                float size, newsize;
                QStringList fileSizeList = xsumList2[1].split('=');               
                size = fileSizeList[1].toFloat();

                if(size >= 1073741824)
                {
                    newsize = size / 1073741824;
                    putSize = QString::number(newsize, 'f', 1) + " GB";
                }
                else if(size >= 1048576)
                {
                    newsize = size / 1048576;
                    putSize = QString::number(newsize, 'f', 1) + " MB";
                }
                else if(size >= 1024)
                {
                    newsize = size / 1024;
                    putSize = QString::number(newsize, 'f', 1) + " KB";
                }
                else
                {
                    putSize = QString::number(size, 'f', 1) + " bytes";
                }

                treeItems[i].addGrandChild(k - 1, column, "File size: " + putSize);
             }

            //Display EOF Cancel sent/received
            QRegExp eofCancelExp("(EOF-Cancel)[ ][(][a-zA-Z0-9-_:()\\/. ]*[)][:][ ][ ](xsum=)[a-zA-Z0-9]*[,][ ](file-size=)[0-9]*");           //checked
            if(eofCancelExp.indexIn(input) != -1)
            {              
                if(recvExp.indexIn(input) != -1) {column = 1; text = "EOF-Cancel received";}
                else {column = 0; text = "EOF-Cancel sent";}

                int k = treeItems[i].addChild(column, orange, text, orangeIcon);

                //Display fault
                QString eofCancelString = eofCancelExp.cap(0);
                QStringList eofCancelList = eofCancelString.split(':');
                QString eofCancelString2 = eofCancelList[0];
                QStringList eofCancelList2 = eofCancelString2.split('(');
                QString eofCancelString3 = eofCancelList2[1];
                QStringList eofCancelList3 = eofCancelString3.split(')');
                treeItems[i].addGrandChild(k - 1, column, "Fault: " + eofCancelList3[0]);

                //Display file checksum
                QString xsumString = eofCancelList[1];
                QStringList xsumList = xsumString.split(',');
                QString xsumString2 = xsumList[0];
                QStringList xsumList2 = xsumString2.split('=');
                treeItems[i].addGrandChild(k - 1, column, "File checksum: " + xsumList2[1]);

                //Display file size
                QString putSize;
                float size, newsize;
                QString fileSizeString = xsumList[1];
                QStringList fileSizeList = fileSizeString.split('=');
                size = fileSizeList[1].toFloat();

                if(size >= 1073741824)
                {
                    newsize = size / 1073741824;
                    putSize = QString::number(newsize, 'f', 1) + " GB";
                }
                else if(size >= 1048576)
                {
                    newsize = size / 1048576;
                    putSize = QString::number(newsize, 'f', 1) + " MB";
                }
                else if(size >= 1024)
                {
                    newsize = size / 1024;
                    putSize = QString::number(newsize, 'f', 1) + " KB";
                }
                else
                {
                    putSize = QString::number(size, 'f', 1) + " bytes";
                }

                treeItems[i].addGrandChild(k - 1, column, "File size: " + putSize);
            }

            //Display ack EOF sent/received
            QRegExp ackEofExp("(Ack-EOF:)");
            if(ackEofExp.indexIn(input) != -1)
            {
                if(recvExp.indexIn(input) != -1) {column = 1; text = "ACK-EOF received";}
                else {column = 0; text = "ACK-EOF sent";}

                treeItems[i].addChild(column, none, text, empty);
            }

            //Display ack EOF cancel sent/received
            QRegExp ackEofCancelExp("(Ack-EOF-Cancel:)");
            if(ackEofCancelExp.indexIn(input) != -1)
            {
                if(recvExp.indexIn(input) != -1) {column = 1; text = "ACK-EOF-Cancel received";}
                else {column = 0; text = "ACK-EOF-Cancel sent";}

                treeItems[i].addChild(column, orange, text, orangeIcon);
            }

            //Dispaly nak metadata sent/received
            QRegExp nakMetadataExp("(Nak:  )[(][0-9]*[-][0-9]*[)][ ](Metadata)[ ]");
            if(nakMetadataExp.indexIn(input) != -1)
            {
                if(recvExp.indexIn(input) != -1) {column = 1; text = "Received NAK";}
                else {column = 0; text = "Sent NAK";}

                int k = treeItems[i].addChild(column, yellow, text, yellowIcon);

                //Display which bytes are missing (metadata)
                treeItems[i].addGrandChild(k - 1, column, "Missing metadata");

                //Display total number of gaps in PDU
                QString gap;
                QRegExp gapExp("[0-9]*[ ](total gaps)");
                if(gapExp.indexIn(input) != -1)
                {
                    QString gapString = gapExp.cap(0);
                    QStringList gapList = gapString.split(' ');
                    gap = gapList[0];
                }
                treeItems[i].addGrandChild(k - 1, column, "Total gaps: " + gap);
            }

            //Display nak sent/received
            QRegExp nakExp("(Nak:  )[(][0-9]*[-][0-9]*[)][ ][0-9]*[-][0-9]*");
            if(nakExp.indexIn(input) != -1)
            {
                if(recvExp.indexIn(input) != -1) {column = 1; text = "Received NAK";}
                else {column = 0; text = "Sent NAK";}

                int k = treeItems[i].addChild(column, yellow, text, yellowIcon);

                //Display which bytes are missing
                QString nakString = nakExp.cap(0);
                QStringList nakList = nakString.split(')');
                QString missing = nakList[1];
                QStringList totalList = nakList[0].split('(');
                QString total = totalList[1];
                treeItems[i].addGrandChild(k - 1, column, "Missing bytes" + missing + " of " + total);

                //Display total number of gaps in PDU
                QString gap;
                QRegExp gapExp("[0-9]*[ ](total gaps)");
                if(gapExp.indexIn(input) != -1)
                {
                    QString gapString = gapExp.cap(0);
                    QStringList gapList = gapString.split(' ');
                    gap = gapList[0];
                }
                treeItems[i].addGrandChild(k - 1, column, "Total gaps: " + gap);
            }

            //Display finished indication sent/received and status
            QRegExp finRecvExp("( Fin)");
            if(finRecvExp.indexIn(input) != -1)
            {
                //Display finished indication for successful transaction
                QRegExp finSuccessExp("( Fin:)");
                if(finSuccessExp.indexIn(input) != -1)
                {
                    if(recvExp.indexIn(input) != -1) {column = 1; text = "Received finished indication";}
                    else {column = 0; text = "Sent finished indication";}

                    treeItems[i].addChild(column, none, text, empty);
                }

                //Display finished indication for cancelled transaction
                QRegExp finCancelExp("( Fin-Cancel)[ ][(][a-zA-Z0-9.:?/\()-_ ]*[)]");
                if(finCancelExp.indexIn(input) != -1)
                {
                    if(recvExp.indexIn(input) != -1) {column = 1; text = "Received finished (canceled) indication";}
                    else {column = 0; text = "Sent finished (canceled) indication";}

                    int k = treeItems[i].addChild(column, orange, text, orangeIcon);

                    //Display fault
                    QString faultString = finCancelExp.cap(0);
                    QStringList faultList = faultString.split('(');
                    QString faultString2 = faultList[1];
                    QStringList faultList2 = faultString2.split(')');
                    treeItems[i].addGrandChild(k - 1, column, "Fault: " + faultList2[0]);
                }
            }

            //Display finished ACK sent/received
            QRegExp finAckExp("(Ack-Fin)");
            if(finAckExp.indexIn(input) != -1)
            {
                //Display finished ACK for successful transaction
                QRegExp ackSuccessExp("(Fin:)");
                if(ackSuccessExp.indexIn(input) != -1)
                {
                    if(recvExp.indexIn(input) != -1) {column = 1; text = "Received finished ACK";}
                    else {column = 0; text = "Sent finished ACK";}

                    treeItems[i].addChild(column, none, text, empty);
                }

                //Display finished ACK for cancelled transaction
                QRegExp ackCancelExp("(Fin-Cancel:)");
                if(ackCancelExp.indexIn(input) != -1)
                {
                    if(recvExp.indexIn(input) != -1) {column = 1; text = "Received finished (canceled) ACK";}
                    else {column = 0; text = "Sent finished (canceled) ACK";}

                    treeItems[i].addChild(column, orange, text, orangeIcon);
                }
            }

            //Display ACK timer expired warning
            QRegExp ackExpExp("(Ack_Timer_Expired)");
            if(ackExpExp.indexIn(input) != -1) treeItems[i].addChild(0, yellow, "ACK timer expired. Resending", yellowIcon);

            //Display NAK timer expired warning
            QRegExp nakExpExp("(Nak_Timer_Expired)");
            if(nakExpExp.indexIn(input) != -1) treeItems[i].addChild(0, yellow, "NAK timer expired. Resending", yellowIcon);

            //Display inactivity timer expired warning
            QRegExp inactivityExpExp("(Inactivity)[_](Timer)[_](Expired)");
            if(inactivityExpExp.indexIn(input) != -1) treeItems[i].addChild(0, yellow, "Inactivity timer expired. Canceling transaction", yellowIcon);

            //Display fault
            QRegExp faultExp("(Fault  trans )[0-9]{2,6}[_][0-9]{1,10}[,]( fault=)['][a-zA-Z0-9.:?/\()-_ ]*[']");         //checked
            if(faultExp.indexIn(input) != -1)
            {
                QString faultString = faultExp.cap(0);
                QStringList faultList = faultString.split('=');

                treeItems[i].addChild(2, orange, "Fault: " + faultList[1], orangeIcon);
            }

            //Display transaction finished and final status
            QRegExp finExp("[(]*.*[ ][-][>][ ]*.*[)][:][ ][a-zA-Z0-9.:?/\()-_ ]*");             //checked
            if(finExp.indexIn(input) != -1)
            {
                QString finStatusString = finExp.cap(0);
                QStringList finStatusList = finStatusString.split(':');

                //Display successful transaction
                if(finStatusList[1].indexOf("successful") != -1)
                {
                    treeItems[i].addChild(2, green, "Transaction " + transNum + " finished:" + finStatusList[1], empty);
                    treeItems[i].topLevelItem->setBackgroundColor(0, green);
                    treeItems[i].topLevelItem->setBackgroundColor(1, green);
                    treeItems[i].topLevelItem->setTextColor(0, black);
                    treeItems[i].topLevelItem->setTextColor(1, black);
                    treeItems[i].status = 0;
                }

                //Display cancelled transaction
                if(finStatusList[1].indexOf("cancelled") != -1)
                {
                    treeItems[i].addChild(2, orange, "Transaction " + transNum + " finished:\n" + finStatusList[1], empty);
                    treeItems[i].topLevelItem->setBackgroundColor(0, orange);
                    treeItems[i].topLevelItem->setBackgroundColor(1, orange);
                    treeItems[i].topLevelItem->setTextColor(0, black);
                    treeItems[i].topLevelItem->setTextColor(1, black);
                    treeItems[i].status = 2;
                }

                //Display abandoned transaction
                if(finStatusList[1].indexOf("abandoned") != -1)
                {
                    treeItems[i].addChild(2, red, "Transaction " + transNum + " finished:\n" + finStatusList[1], empty);
                    treeItems[i].topLevelItem->setBackgroundColor(0, red);
                    treeItems[i].topLevelItem->setBackgroundColor(1, red);
                    treeItems[i].topLevelItem->setTextColor(0, black);
                    treeItems[i].topLevelItem->setTextColor(1, black);
                    treeItems[i].status = 1;
                }
            }

            //Display suspended indication
            QRegExp suspendExp("(Suspended)[ ][ ](trans)");
            if(suspendExp.indexIn(input) != -1) treeItems[i].addChild(2, yellow, "Transaction suspended", yellowIcon);

            //Display resumed indication
            QRegExp resumeExp("(Resumed)[ ][ ](trans)");
            if(resumeExp.indexIn(input) != -1) treeItems[i].addChild(2, none, "Transaction resumed", empty);

            //Display report
            QRegExp reportExp("(Report)[ ][ ](Role=)[a-zA-Z_0-9]*[,][ ](State=)[a-zA-Z_0-9]*[,][ ](Trans=)[0-9]{2,6}[_][0-9]{1,10}[,][ ][0-9]*[ ](of)[ ][0-9]*[ ](bytes sent)[.]");
            if(reportExp.indexIn(input) != -1)
            {
                int k = treeItems[i].addChild(2, none, "Report", empty);

                //Display role
                QString reportString = reportExp.cap(0);
                QStringList reportList = reportString.split(',');
                QStringList roleList = reportList[0].split('=');
                treeItems[i].addGrandChild(k - 1, 2, "Role " + roleList[1]);

                //Display state
                QStringList stateList = reportList[1].split('=');
                treeItems[i].addGrandChild(k - 1, 2, "State: " + stateList[1]);

                //Display transaction progress
                QStringList progressList = reportList[3].split(' ');
                treeItems[i].addGrandChild(k - 1, 2, progressList[1] + " of " + progressList[3] + " bytes sent");
            }
            emit itemAdded();
            found = 1;
      }  }

    //If new transaction
    if (!found)
    {
        //Regular expressions for send vs receive
        QRegExp putExp("(Trans)[ ][ ][0-9]{2,6}[_][0-9]{1,10}");     //[,][ ](class)[ ][1-4][,]
        QRegExp recvExp("(MD_Recv  trans)[ ][0-9]{2,6}[_][0-9]{1,10}");

        //Display information about transaction (sending)
        if(putExp.indexIn(input) != -1)
        {
            //Find transaction class
            QString putClass;
            QRegExp putClassExp("(class)[ ][0-9]");
            if((putClassExp.indexIn(input)) != -1)
            {
                QString putClassString = putClassExp.cap(0);
                QStringList putClassList = putClassString.split(' ');
                putClass = putClassList[1];
            }

            //Find file name
            QString putName;
            QRegExp putNameExp("(sending)[ ][']*.*[']");
            if((putNameExp.indexIn(input)) != -1)
            {
                 QString putNameString = putNameExp.cap(0);
                 QStringList putNameList = putNameString.split(' ');
                 putName = putNameList[1];
            }

            //Find file size
            QString putSize;
            float size, newsize;
            QRegExp putSizeExp("[0-9]*[ ](bytes)");
            if((putSizeExp.indexIn(input)) != -1)
            {
                QString putSizeString = putSizeExp.cap(0);
                QStringList putSizeList = putSizeString.split(' ');
                size = putSizeList[0].toFloat();

                if(size >= 1073741824)
                {
                    newsize = size / 1073741824;
                    putSize = QString::number(newsize, 'f', 1) + " GB";
                }
                else if(size >= 1048576)
                {
                    newsize = size / 1048576;
                    putSize = QString::number(newsize, 'f', 1) + " MB";
                }
                else if(size >= 1024)
                {
                    newsize = size / 1024;
                    putSize = QString::number(newsize, 'f', 1) + " KB";
                }
                else
                {
                    putSize = QString::number(size, 'f', 1) + " bytes";
                }
            }

            //Find node
            QString putNode;
            QRegExp putNodeExp("(node)[ ][0-9]{1,4}");
            if((putNodeExp.indexIn(input)) != -1)
            {
                QString putNodeString = putNodeExp.cap(0);
                QStringList putNodeList = putNodeString.split(' ');
                putNode = putNodeList[1];
            }

            //Display transaction information
            treeItems.push_back(Item(transNum, putClass, putName, putSize, size, putNode));
            ui->tx->addTopLevelItem(treeItems.back().topLevelItem);
            emit itemAdded();
        }

        //Display information about transaction (receiving)
        else if(recvExp.indexIn(input) != -1)
        {
            //Find transaction class
            QString putClass;
            QRegExp putClassExp("(class)[ ][0-9]");
            if((putClassExp.indexIn(input)) != -1)
            {
                QString putClassString = putClassExp.cap(0);
                QStringList putClassList = putClassString.split(' ');
                putClass = putClassList[1];
            }

            //Find file name
            QString putName;
            QRegExp putNameExp("(receiving)[ ][']*.*[']");
            if((putNameExp.indexIn(input)) != -1)
            {
                QString putNameString = putNameExp.cap(0);
                QStringList putNameList = putNameString.split(' ');
                putName = putNameList[1];
            }

            //Find file size
            QString putSize;
            float size, newsize;
            QRegExp putSizeExp("[0-9]*[ ](bytes)");
            if((putSizeExp.indexIn(input)) != -1)
            {
                QString putSizeString = putSizeExp.cap(0);
                QStringList putSizeList = putSizeString.split(' ');
                size = putSizeList[0].toFloat();

                if(size >= 1073741824)
                {
                    newsize = size / 1073741824;

                    putSize = QString::number(newsize, 'f', 1) + " GB";
                }
                else if(size >= 1048576)
                {
                    newsize = size / 1048576;
                    putSize = QString::number(newsize, 'f', 1) + " MB";
                }
                else if(size >= 1024)
                {
                    newsize = size / 1024;
                    putSize = QString::number(newsize, 'f', 1) + " KB";
                }
                else
                {
                    putSize= QString::number(size, 'f', 1) + " bytes";
                }
            }

            //Display transaction information
            treeItems.push_back(Item(transNum, putClass, putName, putSize, size, "N/A"));
            ui->tx->addTopLevelItem(treeItems.back().topLevelItem);

            //Display metadata received
            treeItems.back().addChild(1, none, "Metadata received", empty);

            //Display indication if empty file is sent
            if(input.contains("unbounded file"))
            {
                treeItems.back().addChild(1, red, "Empty file received", empty);
                treeItems.back().topLevelItem->setBackgroundColor(0, red);
                treeItems.back().topLevelItem->setBackgroundColor(1, red);
                treeItems.back().topLevelItem->setTextColor(0, black);
                treeItems.back().topLevelItem->setTextColor(1, black);
            }

            emit itemAdded();
        }
    }
    lastNum = transNum;
    }

    //Display engine is frozen
    else if(freezeExp.indexIn(input) != -1)
    {
        for (unsigned short i = 0; i < treeItems.size(); ++i) treeItems[i].addChild(2, yellow, "Engine is frozen", yellowIcon);
    }

    //Display engine has thawed
    else if(thawExp.indexIn(input) != -1)
    {
        for (unsigned short i = 0; i < treeItems.size(); ++i) treeItems[i].addChild(2, none, "Engine has thawed", empty);
    }

    //Display debug memory use (in message classes)
    else if(memUseExp.indexIn(input) != -1)
    {
        QString memUseString = memUseExp.cap(0);
        QStringList memUseList = memUseString.split(':');
        QString memUse = memUseList[1].simplified();
        memUse.replace("  ", "");

        QString transNum = lastNum;

        for(unsigned short i = 0; i < treeItems.size(); ++i)
        {
            if(transNum == treeItems[i].treeNum) treeItems[i].addChild(0, none, memUse, empty);               //columns?
        }
    }

    //Display debug NAK (in message classes)
    else if((gapExp.indexIn(input) != -1)|(rangeExp.indexIn(input) != -1))
    {
        QString str = input.simplified();
        str.replace("\n", "");

        QString transNum = lastNum;

        for(unsigned short i = 0; i < treeItems.size(); ++i)
        {
            if(transNum == treeItems[i].treeNum) treeItems[i].addChild(0, none, str, empty);             //columns?
        }
    }

    //Display debug PDU (in message classes)
    else if(rawPDUExp.indexIn(input) != -1)
    {
        QString rawPDUString = rawPDUExp.cap(0);
        QStringList rawPDUList = rawPDUString.split(':');

        QString transNum = lastNum;

        for(unsigned short i = 0; i < treeItems.size(); ++i)
        {
            if(transNum == treeItems[i].treeNum)
            {
                int k = treeItems[i].children.size();
                QString str = treeItems[i].children[k-1]->text(0);
                QString str1 = treeItems[i].children[k-1]->text(1);

                if(str.contains("received")|str1.contains("received")|str.contains("--->")|str1.contains("--->"))
                {
                    treeItems[i].addGrandChild(k - 1, 1, "PDU (Raw): " + rawPDUList[1]);
                }
                else treeItems[i].addGrandChild(k - 1, 0, "PDU (Raw): " + rawPDUList[1]);
            }
        }
    }

    //Display debug PDU (in message classes)
    else if(validExp.indexIn(input) != -1)
    {
        QString validString = validExp.cap(0);
        QStringList validList = validString.split(':');

        QString transNum = lastNum;              //can't test that this is always right until we can send larger files, run two at once to see how it differentiates (can go by size if necessary?)

        for(unsigned short i = 0; i < treeItems.size(); ++i)
        {
            if(transNum == treeItems[i].treeNum) treeItems[i].addChild(1, none, "Valid file data received" + validList[1], empty);
        }
    }

    //Display cfdp engine messages
    else if(cfdpEngineExp.indexIn(input) != -1)
    {
        if(treeItems.size() > 0)
        {
            QString engine = cfdpEngineExp.cap(0);
            engine.insert(40, "\n   ");
            engine.insert(83, "\n   ");

            QString transNum = lastNum;

            for(unsigned short i = 0; i < treeItems.size(); ++i)
            {
                if(transNum == treeItems[i].treeNum)
                {
                    int k = treeItems[i].addChild(2, yellow, "CFDP Engine Message", yellowIcon);

                    treeItems[i].addGrandChild(k - 1, 0, engine);

    }   }   }   }

    //If input is not recognized, display
    else
    {
        qDebug() << input;
        //message classes->state all and state change?
    }
}
