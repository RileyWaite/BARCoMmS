/********************************************************************************
** Form generated from reading UI file 'bc_ditl.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BC_DITL_H
#define UI_BC_DITL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BC_DITL
{
public:
    QAction *actionZoom;
    QAction *actionShowLegend;
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QFrame *leftFrame;
    QGridLayout *gridLayout_3;
    QFrame *logoFrame;
    QGridLayout *gridLayout_6;
    QLabel *DITL_BCLOGO;
    QGraphicsView *DITL_graphicsView_LEFT;
    QFrame *splitFrame;
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QFrame *centralFrame;
    QGridLayout *gridLayout_2;
    QGraphicsView *DITL_graphicsView_BOTT;
    QGraphicsView *DITL_graphicsView;
    QFrame *eventTreeFrame;
    QPushButton *expandBut;
    QPushButton *collapseBut;
    QGridLayout *gridLayout;
    QTreeWidget *severityTree;
    QToolBar *DITL_toolBar;
    QStatusBar *DITL_statusBar;

    void setupUi(QMainWindow *BC_DITL)
    {
        if (BC_DITL->objectName().isEmpty())
            BC_DITL->setObjectName(QStringLiteral("BC_DITL"));
        BC_DITL->resize(1700, 750);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BC_DITL->sizePolicy().hasHeightForWidth());
        BC_DITL->setSizePolicy(sizePolicy);
        BC_DITL->setMinimumSize(QSize(1300, 750));
        BC_DITL->setMaximumSize(QSize(1000000, 1000000));
        BC_DITL->setUnifiedTitleAndToolBarOnMac(true);
        actionZoom = new QAction(BC_DITL);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionShowLegend = new QAction(BC_DITL);
        actionShowLegend->setObjectName(QStringLiteral("actionShowLegend"));
        centralWidget = new QWidget(BC_DITL);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(30, 30, 30);"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(3);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        leftFrame = new QFrame(centralWidget);
        leftFrame->setObjectName(QStringLiteral("leftFrame"));
        leftFrame->setFrameShape(QFrame::NoFrame);
        leftFrame->setFrameShadow(QFrame::Raised);
        leftFrame->setLineWidth(0);
        gridLayout_3 = new QGridLayout(leftFrame);
        gridLayout_3->setSpacing(3);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        logoFrame = new QFrame(leftFrame);
        logoFrame->setObjectName(QStringLiteral("logoFrame"));
        logoFrame->setMinimumSize(QSize(274, 70));
        logoFrame->setMaximumSize(QSize(274, 70));
        logoFrame->setFrameShape(QFrame::NoFrame);
        logoFrame->setFrameShadow(QFrame::Raised);
        gridLayout_6 = new QGridLayout(logoFrame);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        DITL_BCLOGO = new QLabel(logoFrame);
        DITL_BCLOGO->setObjectName(QStringLiteral("DITL_BCLOGO"));
        DITL_BCLOGO->setStyleSheet(QStringLiteral("background-color: rgb(30, 30, 30);"));

        gridLayout_6->addWidget(DITL_BCLOGO, 0, 0, 1, 1);


        gridLayout_3->addWidget(logoFrame, 1, 0, 1, 1);

        DITL_graphicsView_LEFT = new QGraphicsView(leftFrame);
        DITL_graphicsView_LEFT->setObjectName(QStringLiteral("DITL_graphicsView_LEFT"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(DITL_graphicsView_LEFT->sizePolicy().hasHeightForWidth());
        DITL_graphicsView_LEFT->setSizePolicy(sizePolicy1);
        DITL_graphicsView_LEFT->setMinimumSize(QSize(274, 611));
        DITL_graphicsView_LEFT->setMaximumSize(QSize(274, 16777215));
        DITL_graphicsView_LEFT->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DITL_graphicsView_LEFT->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_3->addWidget(DITL_graphicsView_LEFT, 0, 0, 1, 1);


        gridLayout_5->addWidget(leftFrame, 0, 0, 1, 1);

        splitFrame = new QFrame(centralWidget);
        splitFrame->setObjectName(QStringLiteral("splitFrame"));
        splitFrame->setFrameShape(QFrame::NoFrame);
        splitFrame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(splitFrame);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(3);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(splitFrame);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setStyleSheet(QLatin1String("QSplitter::handle:horizontal {\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1,\n"
"    stop:0 rgb(60, 60, 60), stop:0.5 rgb(80, 80, 80), stop:1 rgb(60,60,60));\n"
"border: 2px solid rgb(42, 42, 42);\n"
"width: 8px;\n"
"margin-top: 2px;\n"
"margin-bottom: 2px;\n"
"border-radius: 4px;\n"
"}"));
        splitter->setLineWidth(0);
        splitter->setMidLineWidth(7);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(8);
        centralFrame = new QFrame(splitter);
        centralFrame->setObjectName(QStringLiteral("centralFrame"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(centralFrame->sizePolicy().hasHeightForWidth());
        centralFrame->setSizePolicy(sizePolicy2);
        centralFrame->setMinimumSize(QSize(500, 0));
        centralFrame->setFrameShape(QFrame::NoFrame);
        centralFrame->setFrameShadow(QFrame::Raised);
        centralFrame->setLineWidth(0);
        gridLayout_2 = new QGridLayout(centralFrame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(3);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        DITL_graphicsView_BOTT = new QGraphicsView(centralFrame);
        DITL_graphicsView_BOTT->setObjectName(QStringLiteral("DITL_graphicsView_BOTT"));
        DITL_graphicsView_BOTT->setMinimumSize(QSize(0, 70));
        DITL_graphicsView_BOTT->setMaximumSize(QSize(16777215, 70));
        DITL_graphicsView_BOTT->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DITL_graphicsView_BOTT->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(DITL_graphicsView_BOTT, 1, 0, 1, 1);

        DITL_graphicsView = new QGraphicsView(centralFrame);
        DITL_graphicsView->setObjectName(QStringLiteral("DITL_graphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(DITL_graphicsView->sizePolicy().hasHeightForWidth());
        DITL_graphicsView->setSizePolicy(sizePolicy3);
        DITL_graphicsView->setMinimumSize(QSize(0, 611));
        DITL_graphicsView->setLayoutDirection(Qt::LeftToRight);
        DITL_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        DITL_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        gridLayout_2->addWidget(DITL_graphicsView, 0, 0, 1, 1);

        splitter->addWidget(centralFrame);
        eventTreeFrame = new QFrame(splitter);
        eventTreeFrame->setObjectName(QStringLiteral("eventTreeFrame"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(eventTreeFrame->sizePolicy().hasHeightForWidth());
        eventTreeFrame->setSizePolicy(sizePolicy4);
        eventTreeFrame->setFrameShape(QFrame::StyledPanel);
        eventTreeFrame->setFrameShadow(QFrame::Sunken);
        expandBut = new QPushButton(eventTreeFrame);
        expandBut->setObjectName(QStringLiteral("expandBut"));
        expandBut->setGeometry(QRect(5, 4, 80, 18));
        collapseBut = new QPushButton(eventTreeFrame);
        collapseBut->setObjectName(QStringLiteral("collapseBut"));
        collapseBut->setGeometry(QRect(88, 4, 80, 18));
        gridLayout = new QGridLayout(eventTreeFrame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        severityTree = new QTreeWidget(eventTreeFrame);
        QFont font;
        font.setPointSize(11);
        severityTree->headerItem()->setText(0, QString());
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(0, font);
        severityTree->setHeaderItem(__qtreewidgetitem);
        severityTree->setObjectName(QStringLiteral("severityTree"));
        severityTree->setMinimumSize(QSize(420, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Serif"));
        font1.setPointSize(9);
        font1.setKerning(false);
        severityTree->setFont(font1);
        severityTree->setAutoFillBackground(true);
        severityTree->setAlternatingRowColors(true);
        severityTree->setIndentation(15);
        severityTree->setAnimated(false);
        severityTree->setWordWrap(false);

        gridLayout->addWidget(severityTree, 0, 0, 1, 1);

        splitter->addWidget(eventTreeFrame);
        severityTree->raise();
        expandBut->raise();
        collapseBut->raise();

        gridLayout_4->addWidget(splitter, 0, 0, 1, 1);


        gridLayout_5->addWidget(splitFrame, 0, 1, 1, 1);

        BC_DITL->setCentralWidget(centralWidget);
        DITL_toolBar = new QToolBar(BC_DITL);
        DITL_toolBar->setObjectName(QStringLiteral("DITL_toolBar"));
        DITL_toolBar->setOrientation(Qt::Horizontal);
        DITL_toolBar->setIconSize(QSize(20, 20));
        DITL_toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        BC_DITL->addToolBar(Qt::BottomToolBarArea, DITL_toolBar);
        DITL_statusBar = new QStatusBar(BC_DITL);
        DITL_statusBar->setObjectName(QStringLiteral("DITL_statusBar"));
        BC_DITL->setStatusBar(DITL_statusBar);

        DITL_toolBar->addAction(actionShowLegend);
        DITL_toolBar->addAction(actionZoom);

        retranslateUi(BC_DITL);
        QObject::connect(expandBut, SIGNAL(clicked()), severityTree, SLOT(expandAll()));
        QObject::connect(collapseBut, SIGNAL(clicked()), severityTree, SLOT(collapseAll()));

        QMetaObject::connectSlotsByName(BC_DITL);
    } // setupUi

    void retranslateUi(QMainWindow *BC_DITL)
    {
        BC_DITL->setWindowTitle(QApplication::translate("BC_DITL", "Day In The Life - BARCoMmS", 0));
        actionZoom->setText(QApplication::translate("BC_DITL", "Change Zoom", 0));
        actionZoom->setShortcut(QApplication::translate("BC_DITL", "Ctrl++", 0));
        actionShowLegend->setText(QApplication::translate("BC_DITL", "Show Legend", 0));
#ifndef QT_NO_TOOLTIP
        actionShowLegend->setToolTip(QApplication::translate("BC_DITL", "Displays the legend window", 0));
#endif // QT_NO_TOOLTIP
        actionShowLegend->setShortcut(QApplication::translate("BC_DITL", "Ctrl+L", 0));
        DITL_BCLOGO->setText(QString());
        expandBut->setText(QApplication::translate("BC_DITL", "Expand All", 0));
        collapseBut->setText(QApplication::translate("BC_DITL", "Collapse All", 0));
        DITL_toolBar->setWindowTitle(QApplication::translate("BC_DITL", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class BC_DITL: public Ui_BC_DITL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BC_DITL_H
