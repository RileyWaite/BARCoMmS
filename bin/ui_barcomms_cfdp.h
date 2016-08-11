/********************************************************************************
** Form generated from reading UI file 'barcomms_cfdp.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARCOMMS_CFDP_H
#define UI_BARCOMMS_CFDP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BARCoMmS_CFDP
{
public:
    QAction *action_logEvents;
    QAction *action_setBufferSize;
    QAction *action_clearScreen;
    QAction *action_exit;
    QAction *action_commands;
    QAction *action_options;
    QAction *actionAuto_Scroll;
    QAction *action_autoScroll;
    QWidget *centralWidget;
    QGroupBox *groupBox_helpAndExit;
    QPushButton *pushButton_help;
    QPushButton *pushButton_exit;
    QPlainTextEdit *plainTextEdit_output;
    QGroupBox *groupBox_requests;
    QPushButton *pushButton_abandon;
    QPushButton *pushButton_report;
    QPushButton *pushButton_resume;
    QPushButton *pushButton_suspend;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_put;
    QGroupBox *groupBox_engineToggles;
    QPushButton *pushButton_disableEngineMessages;
    QPushButton *pushButton_freeze;
    QGroupBox *groupBox_misc;
    QPushButton *pushButton_robust;
    QPushButton *pushButton_echo;
    QLineEdit *lineEdit_input;
    QGroupBox *groupBox_statuses;
    QPushButton *pushButton_transStatus;
    QPushButton *pushButton_detailedStatus;
    QPushButton *pushButton_summary;
    QPushButton *pushButton_list;
    QPushButton *pushButton_resetTotals;
    QPushButton *pushButton_periodicStatus;
    QGroupBox *groupBox_engineSettings;
    QPushButton *pushButton_setter;
    QPushButton *pushButton_classMessages;
    QPushButton *pushButton_sim;
    QLabel *label_logo;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *BARCoMmS_CFDP)
    {
        if (BARCoMmS_CFDP->objectName().isEmpty())
            BARCoMmS_CFDP->setObjectName(QStringLiteral("BARCoMmS_CFDP"));
        BARCoMmS_CFDP->resize(1071, 721);
        BARCoMmS_CFDP->setMinimumSize(QSize(1071, 721));
        BARCoMmS_CFDP->setMaximumSize(QSize(1071, 721));
        QFont font;
        font.setPointSize(9);
        BARCoMmS_CFDP->setFont(font);
        action_logEvents = new QAction(BARCoMmS_CFDP);
        action_logEvents->setObjectName(QStringLiteral("action_logEvents"));
        action_logEvents->setCheckable(true);
        action_setBufferSize = new QAction(BARCoMmS_CFDP);
        action_setBufferSize->setObjectName(QStringLiteral("action_setBufferSize"));
        action_clearScreen = new QAction(BARCoMmS_CFDP);
        action_clearScreen->setObjectName(QStringLiteral("action_clearScreen"));
        action_exit = new QAction(BARCoMmS_CFDP);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_commands = new QAction(BARCoMmS_CFDP);
        action_commands->setObjectName(QStringLiteral("action_commands"));
        action_options = new QAction(BARCoMmS_CFDP);
        action_options->setObjectName(QStringLiteral("action_options"));
        actionAuto_Scroll = new QAction(BARCoMmS_CFDP);
        actionAuto_Scroll->setObjectName(QStringLiteral("actionAuto_Scroll"));
        action_autoScroll = new QAction(BARCoMmS_CFDP);
        action_autoScroll->setObjectName(QStringLiteral("action_autoScroll"));
        action_autoScroll->setCheckable(true);
        action_autoScroll->setChecked(true);
        centralWidget = new QWidget(BARCoMmS_CFDP);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox_helpAndExit = new QGroupBox(centralWidget);
        groupBox_helpAndExit->setObjectName(QStringLiteral("groupBox_helpAndExit"));
        groupBox_helpAndExit->setGeometry(QRect(930, 530, 121, 101));
        pushButton_help = new QPushButton(groupBox_helpAndExit);
        pushButton_help->setObjectName(QStringLiteral("pushButton_help"));
        pushButton_help->setGeometry(QRect(10, 30, 101, 28));
        pushButton_exit = new QPushButton(groupBox_helpAndExit);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(10, 60, 101, 28));
        plainTextEdit_output = new QPlainTextEdit(centralWidget);
        plainTextEdit_output->setObjectName(QStringLiteral("plainTextEdit_output"));
        plainTextEdit_output->setGeometry(QRect(160, 80, 751, 551));
        plainTextEdit_output->setAutoFillBackground(false);
        plainTextEdit_output->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        plainTextEdit_output->setReadOnly(true);
        plainTextEdit_output->setTextInteractionFlags(Qt::NoTextInteraction);
        plainTextEdit_output->setMaximumBlockCount(500);
        groupBox_requests = new QGroupBox(centralWidget);
        groupBox_requests->setObjectName(QStringLiteral("groupBox_requests"));
        groupBox_requests->setGeometry(QRect(20, 60, 121, 221));
        pushButton_abandon = new QPushButton(groupBox_requests);
        pushButton_abandon->setObjectName(QStringLiteral("pushButton_abandon"));
        pushButton_abandon->setGeometry(QRect(10, 150, 101, 28));
        pushButton_report = new QPushButton(groupBox_requests);
        pushButton_report->setObjectName(QStringLiteral("pushButton_report"));
        pushButton_report->setGeometry(QRect(10, 180, 101, 28));
        pushButton_resume = new QPushButton(groupBox_requests);
        pushButton_resume->setObjectName(QStringLiteral("pushButton_resume"));
        pushButton_resume->setGeometry(QRect(10, 90, 101, 28));
        pushButton_suspend = new QPushButton(groupBox_requests);
        pushButton_suspend->setObjectName(QStringLiteral("pushButton_suspend"));
        pushButton_suspend->setGeometry(QRect(10, 60, 101, 28));
        pushButton_cancel = new QPushButton(groupBox_requests);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(10, 120, 101, 28));
        pushButton_put = new QPushButton(groupBox_requests);
        pushButton_put->setObjectName(QStringLiteral("pushButton_put"));
        pushButton_put->setGeometry(QRect(10, 30, 101, 28));
        groupBox_engineToggles = new QGroupBox(centralWidget);
        groupBox_engineToggles->setObjectName(QStringLiteral("groupBox_engineToggles"));
        groupBox_engineToggles->setGeometry(QRect(930, 60, 121, 151));
        pushButton_disableEngineMessages = new QPushButton(groupBox_engineToggles);
        pushButton_disableEngineMessages->setObjectName(QStringLiteral("pushButton_disableEngineMessages"));
        pushButton_disableEngineMessages->setGeometry(QRect(10, 80, 101, 61));
        pushButton_disableEngineMessages->setCheckable(true);
        pushButton_freeze = new QPushButton(groupBox_engineToggles);
        pushButton_freeze->setObjectName(QStringLiteral("pushButton_freeze"));
        pushButton_freeze->setGeometry(QRect(10, 30, 101, 51));
        pushButton_freeze->setCheckable(true);
        groupBox_misc = new QGroupBox(centralWidget);
        groupBox_misc->setObjectName(QStringLiteral("groupBox_misc"));
        groupBox_misc->setGeometry(QRect(930, 400, 121, 121));
        pushButton_robust = new QPushButton(groupBox_misc);
        pushButton_robust->setObjectName(QStringLiteral("pushButton_robust"));
        pushButton_robust->setGeometry(QRect(10, 30, 101, 51));
        pushButton_echo = new QPushButton(groupBox_misc);
        pushButton_echo->setObjectName(QStringLiteral("pushButton_echo"));
        pushButton_echo->setGeometry(QRect(10, 80, 101, 28));
        pushButton_echo->setCheckable(true);
        lineEdit_input = new QLineEdit(centralWidget);
        lineEdit_input->setObjectName(QStringLiteral("lineEdit_input"));
        lineEdit_input->setEnabled(true);
        lineEdit_input->setGeometry(QRect(160, 630, 751, 21));
        groupBox_statuses = new QGroupBox(centralWidget);
        groupBox_statuses->setObjectName(QStringLiteral("groupBox_statuses"));
        groupBox_statuses->setGeometry(QRect(20, 330, 121, 301));
        pushButton_transStatus = new QPushButton(groupBox_statuses);
        pushButton_transStatus->setObjectName(QStringLiteral("pushButton_transStatus"));
        pushButton_transStatus->setGeometry(QRect(10, 130, 101, 51));
        pushButton_detailedStatus = new QPushButton(groupBox_statuses);
        pushButton_detailedStatus->setObjectName(QStringLiteral("pushButton_detailedStatus"));
        pushButton_detailedStatus->setGeometry(QRect(10, 30, 101, 51));
        pushButton_summary = new QPushButton(groupBox_statuses);
        pushButton_summary->setObjectName(QStringLiteral("pushButton_summary"));
        pushButton_summary->setGeometry(QRect(10, 210, 101, 28));
        pushButton_list = new QPushButton(groupBox_statuses);
        pushButton_list->setObjectName(QStringLiteral("pushButton_list"));
        pushButton_list->setGeometry(QRect(10, 180, 101, 28));
        pushButton_resetTotals = new QPushButton(groupBox_statuses);
        pushButton_resetTotals->setObjectName(QStringLiteral("pushButton_resetTotals"));
        pushButton_resetTotals->setGeometry(QRect(10, 240, 101, 51));
        pushButton_periodicStatus = new QPushButton(groupBox_statuses);
        pushButton_periodicStatus->setObjectName(QStringLiteral("pushButton_periodicStatus"));
        pushButton_periodicStatus->setGeometry(QRect(10, 80, 101, 51));
        pushButton_periodicStatus->setCheckable(true);
        groupBox_engineSettings = new QGroupBox(centralWidget);
        groupBox_engineSettings->setObjectName(QStringLiteral("groupBox_engineSettings"));
        groupBox_engineSettings->setGeometry(QRect(930, 220, 121, 171));
        pushButton_setter = new QPushButton(groupBox_engineSettings);
        pushButton_setter->setObjectName(QStringLiteral("pushButton_setter"));
        pushButton_setter->setGeometry(QRect(10, 30, 101, 31));
        pushButton_classMessages = new QPushButton(groupBox_engineSettings);
        pushButton_classMessages->setObjectName(QStringLiteral("pushButton_classMessages"));
        pushButton_classMessages->setGeometry(QRect(10, 60, 101, 51));
        pushButton_sim = new QPushButton(groupBox_engineSettings);
        pushButton_sim->setObjectName(QStringLiteral("pushButton_sim"));
        pushButton_sim->setGeometry(QRect(10, 110, 101, 51));
        label_logo = new QLabel(centralWidget);
        label_logo->setObjectName(QStringLiteral("label_logo"));
        label_logo->setGeometry(QRect(430, 0, 211, 71));
        label_logo->setMinimumSize(QSize(211, 71));
        label_logo->setMaximumSize(QSize(211, 71));
        BARCoMmS_CFDP->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BARCoMmS_CFDP);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1071, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        BARCoMmS_CFDP->setMenuBar(menuBar);
        QWidget::setTabOrder(lineEdit_input, plainTextEdit_output);
        QWidget::setTabOrder(plainTextEdit_output, pushButton_put);
        QWidget::setTabOrder(pushButton_put, pushButton_suspend);
        QWidget::setTabOrder(pushButton_suspend, pushButton_resume);
        QWidget::setTabOrder(pushButton_resume, pushButton_cancel);
        QWidget::setTabOrder(pushButton_cancel, pushButton_abandon);
        QWidget::setTabOrder(pushButton_abandon, pushButton_report);
        QWidget::setTabOrder(pushButton_report, pushButton_detailedStatus);
        QWidget::setTabOrder(pushButton_detailedStatus, pushButton_periodicStatus);
        QWidget::setTabOrder(pushButton_periodicStatus, pushButton_transStatus);
        QWidget::setTabOrder(pushButton_transStatus, pushButton_list);
        QWidget::setTabOrder(pushButton_list, pushButton_summary);
        QWidget::setTabOrder(pushButton_summary, pushButton_resetTotals);
        QWidget::setTabOrder(pushButton_resetTotals, pushButton_freeze);
        QWidget::setTabOrder(pushButton_freeze, pushButton_disableEngineMessages);
        QWidget::setTabOrder(pushButton_disableEngineMessages, pushButton_setter);
        QWidget::setTabOrder(pushButton_setter, pushButton_classMessages);
        QWidget::setTabOrder(pushButton_classMessages, pushButton_sim);
        QWidget::setTabOrder(pushButton_sim, pushButton_robust);
        QWidget::setTabOrder(pushButton_robust, pushButton_echo);
        QWidget::setTabOrder(pushButton_echo, pushButton_help);
        QWidget::setTabOrder(pushButton_help, pushButton_exit);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_autoScroll);
        menuFile->addAction(action_logEvents);
        menuFile->addAction(action_setBufferSize);
        menuFile->addAction(action_clearScreen);
        menuFile->addSeparator();
        menuFile->addAction(action_options);
        menuFile->addSeparator();
        menuFile->addAction(action_exit);
        menuHelp->addAction(action_commands);

        retranslateUi(BARCoMmS_CFDP);

        QMetaObject::connectSlotsByName(BARCoMmS_CFDP);
    } // setupUi

    void retranslateUi(QMainWindow *BARCoMmS_CFDP)
    {
        BARCoMmS_CFDP->setWindowTitle(QApplication::translate("BARCoMmS_CFDP", "CFDP - BARCoMmS", 0));
        action_logEvents->setText(QApplication::translate("BARCoMmS_CFDP", "Log Events", 0));
        action_logEvents->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+L", 0));
        action_setBufferSize->setText(QApplication::translate("BARCoMmS_CFDP", "Set Buffer Size", 0));
        action_setBufferSize->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+B", 0));
        action_clearScreen->setText(QApplication::translate("BARCoMmS_CFDP", "Clear Screen", 0));
        action_clearScreen->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+S", 0));
        action_exit->setText(QApplication::translate("BARCoMmS_CFDP", "Exit", 0));
        action_exit->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+Q", 0));
        action_commands->setText(QApplication::translate("BARCoMmS_CFDP", "Commands", 0));
        action_commands->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+D", 0));
        action_options->setText(QApplication::translate("BARCoMmS_CFDP", "Options", 0));
        action_options->setShortcut(QApplication::translate("BARCoMmS_CFDP", "Ctrl+O", 0));
        actionAuto_Scroll->setText(QApplication::translate("BARCoMmS_CFDP", "Auto-Scroll", 0));
        action_autoScroll->setText(QApplication::translate("BARCoMmS_CFDP", "Auto Scroll", 0));
        groupBox_helpAndExit->setTitle(QApplication::translate("BARCoMmS_CFDP", "Help/Exit", 0));
        pushButton_help->setText(QApplication::translate("BARCoMmS_CFDP", "Help", 0));
        pushButton_exit->setText(QApplication::translate("BARCoMmS_CFDP", "Exit", 0));
        groupBox_requests->setTitle(QApplication::translate("BARCoMmS_CFDP", "Requests", 0));
        pushButton_abandon->setText(QApplication::translate("BARCoMmS_CFDP", "Abandon", 0));
        pushButton_report->setText(QApplication::translate("BARCoMmS_CFDP", "Report", 0));
        pushButton_resume->setText(QApplication::translate("BARCoMmS_CFDP", "Resume", 0));
        pushButton_suspend->setText(QApplication::translate("BARCoMmS_CFDP", "Suspend", 0));
        pushButton_cancel->setText(QApplication::translate("BARCoMmS_CFDP", "Cancel", 0));
        pushButton_put->setText(QApplication::translate("BARCoMmS_CFDP", "Put", 0));
        groupBox_engineToggles->setTitle(QApplication::translate("BARCoMmS_CFDP", "Engine Toggles", 0));
        pushButton_disableEngineMessages->setText(QApplication::translate("BARCoMmS_CFDP", "Disable\n"
"Engine\n"
"Messages", 0));
        pushButton_freeze->setText(QApplication::translate("BARCoMmS_CFDP", "Freeze\n"
"Engine", 0));
        groupBox_misc->setTitle(QApplication::translate("BARCoMmS_CFDP", "Misc.", 0));
        pushButton_robust->setText(QApplication::translate("BARCoMmS_CFDP", "Robustness\n"
"Test", 0));
        pushButton_echo->setText(QApplication::translate("BARCoMmS_CFDP", "Echo", 0));
        groupBox_statuses->setTitle(QApplication::translate("BARCoMmS_CFDP", "Statuses", 0));
        pushButton_transStatus->setText(QApplication::translate("BARCoMmS_CFDP", "Trans\n"
"Status", 0));
        pushButton_detailedStatus->setText(QApplication::translate("BARCoMmS_CFDP", "Detailed\n"
"Status", 0));
        pushButton_summary->setText(QApplication::translate("BARCoMmS_CFDP", "Summary", 0));
        pushButton_list->setText(QApplication::translate("BARCoMmS_CFDP", "List", 0));
        pushButton_resetTotals->setText(QApplication::translate("BARCoMmS_CFDP", "Reset\n"
"Totals", 0));
        pushButton_periodicStatus->setText(QApplication::translate("BARCoMmS_CFDP", "Periodic\n"
"Status", 0));
        groupBox_engineSettings->setTitle(QApplication::translate("BARCoMmS_CFDP", "Engine Settings", 0));
        pushButton_setter->setText(QApplication::translate("BARCoMmS_CFDP", "MIB", 0));
        pushButton_classMessages->setText(QApplication::translate("BARCoMmS_CFDP", "Message\n"
"Classes", 0));
        pushButton_sim->setText(QApplication::translate("BARCoMmS_CFDP", "Link\n"
"Simulator", 0));
        label_logo->setText(QString());
        menuFile->setTitle(QApplication::translate("BARCoMmS_CFDP", "File", 0));
        menuHelp->setTitle(QApplication::translate("BARCoMmS_CFDP", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class BARCoMmS_CFDP: public Ui_BARCoMmS_CFDP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARCOMMS_CFDP_H
