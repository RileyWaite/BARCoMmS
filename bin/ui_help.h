/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_availableCommands;
    QLabel *label_simExample;
    QLabel *label_reportExample;
    QLabel *label_transStatus;
    QLabel *label_detailedStatusExample;
    QLabel *label_suspend;
    QLabel *label_listExample;
    QLabel *label_periodicStatusExample;
    QLabel *label_list;
    QLabel *label_summary;
    QLabel *label_resume;
    QLabel *label_abandon;
    QLabel *label_get;
    QLabel *label_enableExample;
    QLabel *label_mib;
    QLabel *label_freeze;
    QLabel *label_disable;
    QLabel *label_suspendExample;
    QLabel *label_enable;
    QLabel *label_detailedStatus;
    QLabel *label_exitExample;
    QLabel *label_abandonExample;
    QLabel *label_robustExample;
    QLabel *label_periodicStatus;
    QLabel *label_thaw;
    QLabel *label_p2Misc;
    QLabel *label_summaryExample;
    QLabel *label_mibExample;
    QLabel *label_sim;
    QLabel *label_classMinus;
    QLabel *label_cancelExample;
    QLabel *label_getExample;
    QLabel *label_thawExample;
    QLabel *label_resetTotals;
    QLabel *label_classPlus;
    QLabel *label_updateExample;
    QLabel *label_transStatusExample;
    QLabel *label_p1Misc;
    QLabel *label_resumeExample;
    QLabel *label_robust;
    QLabel *label_report;
    QLabel *label_cancel;
    QLabel *label_update;
    QLabel *label_classMinusExample;
    QLabel *label_disableExample;
    QLabel *label_resetTotalsExample;
    QLabel *label_classPlusExample;
    QLabel *label_putExample;
    QLabel *label_freezeExample;
    QLabel *label_help;
    QLabel *label_exit;
    QLabel *label_helpExample;
    QLabel *label_numberMisc;
    QLabel *label_put;
    QLabel *label_echoExample;
    QLabel *label_echo;
    QLabel *label_setExample;
    QLabel *label_set;

    void setupUi(QDialog *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QStringLiteral("Help"));
        Help->resize(671, 751);
        Help->setMinimumSize(QSize(671, 751));
        Help->setMaximumSize(QSize(671, 751));
        buttonBox = new QDialogButtonBox(Help);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 700, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close);
        groupBox_availableCommands = new QGroupBox(Help);
        groupBox_availableCommands->setObjectName(QStringLiteral("groupBox_availableCommands"));
        groupBox_availableCommands->setGeometry(QRect(20, 20, 631, 661));
        label_simExample = new QLabel(groupBox_availableCommands);
        label_simExample->setObjectName(QStringLiteral("label_simExample"));
        label_simExample->setGeometry(QRect(390, 470, 191, 16));
        label_reportExample = new QLabel(groupBox_availableCommands);
        label_reportExample->setObjectName(QStringLiteral("label_reportExample"));
        label_reportExample->setGeometry(QRect(390, 130, 191, 16));
        label_transStatus = new QLabel(groupBox_availableCommands);
        label_transStatus->setObjectName(QStringLiteral("label_transStatus"));
        label_transStatus->setGeometry(QRect(20, 210, 371, 20));
        label_detailedStatusExample = new QLabel(groupBox_availableCommands);
        label_detailedStatusExample->setObjectName(QStringLiteral("label_detailedStatusExample"));
        label_detailedStatusExample->setGeometry(QRect(390, 150, 191, 16));
        label_suspend = new QLabel(groupBox_availableCommands);
        label_suspend->setObjectName(QStringLiteral("label_suspend"));
        label_suspend->setGeometry(QRect(20, 50, 371, 20));
        label_listExample = new QLabel(groupBox_availableCommands);
        label_listExample->setObjectName(QStringLiteral("label_listExample"));
        label_listExample->setGeometry(QRect(390, 230, 191, 16));
        label_periodicStatusExample = new QLabel(groupBox_availableCommands);
        label_periodicStatusExample->setObjectName(QStringLiteral("label_periodicStatusExample"));
        label_periodicStatusExample->setGeometry(QRect(390, 190, 191, 16));
        label_list = new QLabel(groupBox_availableCommands);
        label_list->setObjectName(QStringLiteral("label_list"));
        label_list->setGeometry(QRect(20, 230, 371, 20));
        label_summary = new QLabel(groupBox_availableCommands);
        label_summary->setObjectName(QStringLiteral("label_summary"));
        label_summary->setGeometry(QRect(20, 250, 371, 20));
        label_resume = new QLabel(groupBox_availableCommands);
        label_resume->setObjectName(QStringLiteral("label_resume"));
        label_resume->setGeometry(QRect(20, 70, 371, 20));
        label_abandon = new QLabel(groupBox_availableCommands);
        label_abandon->setObjectName(QStringLiteral("label_abandon"));
        label_abandon->setGeometry(QRect(20, 110, 371, 20));
        label_get = new QLabel(groupBox_availableCommands);
        label_get->setObjectName(QStringLiteral("label_get"));
        label_get->setGeometry(QRect(20, 410, 371, 20));
        label_enableExample = new QLabel(groupBox_availableCommands);
        label_enableExample->setObjectName(QStringLiteral("label_enableExample"));
        label_enableExample->setGeometry(QRect(390, 350, 191, 16));
        label_mib = new QLabel(groupBox_availableCommands);
        label_mib->setObjectName(QStringLiteral("label_mib"));
        label_mib->setGeometry(QRect(20, 370, 371, 20));
        label_freeze = new QLabel(groupBox_availableCommands);
        label_freeze->setObjectName(QStringLiteral("label_freeze"));
        label_freeze->setGeometry(QRect(20, 290, 371, 20));
        label_disable = new QLabel(groupBox_availableCommands);
        label_disable->setObjectName(QStringLiteral("label_disable"));
        label_disable->setGeometry(QRect(20, 330, 371, 20));
        label_suspendExample = new QLabel(groupBox_availableCommands);
        label_suspendExample->setObjectName(QStringLiteral("label_suspendExample"));
        label_suspendExample->setGeometry(QRect(390, 50, 191, 16));
        label_enable = new QLabel(groupBox_availableCommands);
        label_enable->setObjectName(QStringLiteral("label_enable"));
        label_enable->setGeometry(QRect(20, 350, 371, 20));
        label_detailedStatus = new QLabel(groupBox_availableCommands);
        label_detailedStatus->setObjectName(QStringLiteral("label_detailedStatus"));
        label_detailedStatus->setGeometry(QRect(20, 150, 371, 20));
        label_exitExample = new QLabel(groupBox_availableCommands);
        label_exitExample->setObjectName(QStringLiteral("label_exitExample"));
        label_exitExample->setGeometry(QRect(390, 550, 191, 16));
        label_abandonExample = new QLabel(groupBox_availableCommands);
        label_abandonExample->setObjectName(QStringLiteral("label_abandonExample"));
        label_abandonExample->setGeometry(QRect(390, 110, 191, 16));
        label_robustExample = new QLabel(groupBox_availableCommands);
        label_robustExample->setObjectName(QStringLiteral("label_robustExample"));
        label_robustExample->setGeometry(QRect(390, 490, 191, 20));
        label_periodicStatus = new QLabel(groupBox_availableCommands);
        label_periodicStatus->setObjectName(QStringLiteral("label_periodicStatus"));
        label_periodicStatus->setGeometry(QRect(20, 190, 371, 20));
        label_thaw = new QLabel(groupBox_availableCommands);
        label_thaw->setObjectName(QStringLiteral("label_thaw"));
        label_thaw->setGeometry(QRect(20, 310, 371, 20));
        label_p2Misc = new QLabel(groupBox_availableCommands);
        label_p2Misc->setObjectName(QStringLiteral("label_p2Misc"));
        label_p2Misc->setGeometry(QRect(20, 630, 371, 16));
        label_summaryExample = new QLabel(groupBox_availableCommands);
        label_summaryExample->setObjectName(QStringLiteral("label_summaryExample"));
        label_summaryExample->setGeometry(QRect(390, 250, 191, 20));
        label_mibExample = new QLabel(groupBox_availableCommands);
        label_mibExample->setObjectName(QStringLiteral("label_mibExample"));
        label_mibExample->setGeometry(QRect(390, 370, 191, 16));
        label_sim = new QLabel(groupBox_availableCommands);
        label_sim->setObjectName(QStringLiteral("label_sim"));
        label_sim->setGeometry(QRect(20, 470, 371, 20));
        label_classMinus = new QLabel(groupBox_availableCommands);
        label_classMinus->setObjectName(QStringLiteral("label_classMinus"));
        label_classMinus->setGeometry(QRect(20, 450, 371, 20));
        label_cancelExample = new QLabel(groupBox_availableCommands);
        label_cancelExample->setObjectName(QStringLiteral("label_cancelExample"));
        label_cancelExample->setGeometry(QRect(390, 90, 191, 16));
        label_getExample = new QLabel(groupBox_availableCommands);
        label_getExample->setObjectName(QStringLiteral("label_getExample"));
        label_getExample->setGeometry(QRect(390, 410, 191, 16));
        label_thawExample = new QLabel(groupBox_availableCommands);
        label_thawExample->setObjectName(QStringLiteral("label_thawExample"));
        label_thawExample->setGeometry(QRect(390, 310, 191, 16));
        label_resetTotals = new QLabel(groupBox_availableCommands);
        label_resetTotals->setObjectName(QStringLiteral("label_resetTotals"));
        label_resetTotals->setGeometry(QRect(20, 270, 371, 20));
        label_classPlus = new QLabel(groupBox_availableCommands);
        label_classPlus->setObjectName(QStringLiteral("label_classPlus"));
        label_classPlus->setGeometry(QRect(20, 430, 371, 20));
        label_updateExample = new QLabel(groupBox_availableCommands);
        label_updateExample->setObjectName(QStringLiteral("label_updateExample"));
        label_updateExample->setGeometry(QRect(390, 170, 191, 16));
        label_transStatusExample = new QLabel(groupBox_availableCommands);
        label_transStatusExample->setObjectName(QStringLiteral("label_transStatusExample"));
        label_transStatusExample->setGeometry(QRect(390, 210, 191, 16));
        label_p1Misc = new QLabel(groupBox_availableCommands);
        label_p1Misc->setObjectName(QStringLiteral("label_p1Misc"));
        label_p1Misc->setGeometry(QRect(20, 610, 371, 16));
        label_resumeExample = new QLabel(groupBox_availableCommands);
        label_resumeExample->setObjectName(QStringLiteral("label_resumeExample"));
        label_resumeExample->setGeometry(QRect(390, 70, 191, 16));
        label_robust = new QLabel(groupBox_availableCommands);
        label_robust->setObjectName(QStringLiteral("label_robust"));
        label_robust->setGeometry(QRect(20, 490, 371, 20));
        label_report = new QLabel(groupBox_availableCommands);
        label_report->setObjectName(QStringLiteral("label_report"));
        label_report->setGeometry(QRect(20, 130, 371, 20));
        label_cancel = new QLabel(groupBox_availableCommands);
        label_cancel->setObjectName(QStringLiteral("label_cancel"));
        label_cancel->setGeometry(QRect(20, 90, 371, 20));
        label_update = new QLabel(groupBox_availableCommands);
        label_update->setObjectName(QStringLiteral("label_update"));
        label_update->setGeometry(QRect(20, 170, 371, 20));
        label_classMinusExample = new QLabel(groupBox_availableCommands);
        label_classMinusExample->setObjectName(QStringLiteral("label_classMinusExample"));
        label_classMinusExample->setGeometry(QRect(390, 450, 191, 16));
        label_disableExample = new QLabel(groupBox_availableCommands);
        label_disableExample->setObjectName(QStringLiteral("label_disableExample"));
        label_disableExample->setGeometry(QRect(390, 330, 191, 16));
        label_resetTotalsExample = new QLabel(groupBox_availableCommands);
        label_resetTotalsExample->setObjectName(QStringLiteral("label_resetTotalsExample"));
        label_resetTotalsExample->setGeometry(QRect(390, 270, 191, 16));
        label_classPlusExample = new QLabel(groupBox_availableCommands);
        label_classPlusExample->setObjectName(QStringLiteral("label_classPlusExample"));
        label_classPlusExample->setGeometry(QRect(390, 430, 191, 20));
        label_putExample = new QLabel(groupBox_availableCommands);
        label_putExample->setObjectName(QStringLiteral("label_putExample"));
        label_putExample->setGeometry(QRect(390, 30, 191, 16));
        label_freezeExample = new QLabel(groupBox_availableCommands);
        label_freezeExample->setObjectName(QStringLiteral("label_freezeExample"));
        label_freezeExample->setGeometry(QRect(390, 290, 191, 16));
        label_help = new QLabel(groupBox_availableCommands);
        label_help->setObjectName(QStringLiteral("label_help"));
        label_help->setGeometry(QRect(20, 530, 371, 20));
        label_exit = new QLabel(groupBox_availableCommands);
        label_exit->setObjectName(QStringLiteral("label_exit"));
        label_exit->setGeometry(QRect(20, 550, 371, 20));
        label_helpExample = new QLabel(groupBox_availableCommands);
        label_helpExample->setObjectName(QStringLiteral("label_helpExample"));
        label_helpExample->setGeometry(QRect(390, 530, 191, 20));
        label_numberMisc = new QLabel(groupBox_availableCommands);
        label_numberMisc->setObjectName(QStringLiteral("label_numberMisc"));
        label_numberMisc->setGeometry(QRect(20, 590, 371, 16));
        label_put = new QLabel(groupBox_availableCommands);
        label_put->setObjectName(QStringLiteral("label_put"));
        label_put->setGeometry(QRect(20, 30, 371, 20));
        label_echoExample = new QLabel(groupBox_availableCommands);
        label_echoExample->setObjectName(QStringLiteral("label_echoExample"));
        label_echoExample->setGeometry(QRect(390, 510, 191, 16));
        label_echo = new QLabel(groupBox_availableCommands);
        label_echo->setObjectName(QStringLiteral("label_echo"));
        label_echo->setGeometry(QRect(20, 510, 371, 20));
        label_setExample = new QLabel(groupBox_availableCommands);
        label_setExample->setObjectName(QStringLiteral("label_setExample"));
        label_setExample->setGeometry(QRect(390, 390, 191, 16));
        label_set = new QLabel(groupBox_availableCommands);
        label_set->setObjectName(QStringLiteral("label_set"));
        label_set->setGeometry(QRect(20, 390, 371, 20));

        retranslateUi(Help);
        QObject::connect(buttonBox, SIGNAL(accepted()), Help, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Help, SLOT(reject()));

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QDialog *Help)
    {
        Help->setWindowTitle(QApplication::translate("Help", "Help", 0));
        groupBox_availableCommands->setTitle(QApplication::translate("Help", "Available Commands", 0));
        label_simExample->setText(QApplication::translate("Help", "sim normal", 0));
        label_reportExample->setText(QApplication::translate("Help", "report 23_4", 0));
        label_transStatus->setText(QApplication::translate("Help", "To see trans status once......................................", 0));
        label_detailedStatusExample->setText(QApplication::translate("Help", "detailed_status 23_5", 0));
        label_suspend->setText(QApplication::translate("Help", "To suspend a transaction (example)....................", 0));
        label_listExample->setText(QApplication::translate("Help", "l[ist]", 0));
        label_periodicStatusExample->setText(QApplication::translate("Help", "n", 0));
        label_list->setText(QApplication::translate("Help", "To see a list of transactions.................................", 0));
        label_summary->setText(QApplication::translate("Help", "To see summary engine status............................", 0));
        label_resume->setText(QApplication::translate("Help", "To resume a transaction (example).....................", 0));
        label_abandon->setText(QApplication::translate("Help", "To abandon a transaction (example)...................", 0));
        label_get->setText(QApplication::translate("Help", "To get MIB parameter (example).........................", 0));
        label_enableExample->setText(QApplication::translate("Help", "en[able_messages]", 0));
        label_mib->setText(QApplication::translate("Help", "To see MIB as string.............................................", 0));
        label_freeze->setText(QApplication::translate("Help", "To freeze engine..................................................", 0));
        label_disable->setText(QApplication::translate("Help", "To disable engine messages................................", 0));
        label_suspendExample->setText(QApplication::translate("Help", "suspend all", 0));
        label_enable->setText(QApplication::translate("Help", "To enable engine messages.................................", 0));
        label_detailedStatus->setText(QApplication::translate("Help", "To see detailed status (example).........................", 0));
        label_exitExample->setText(QApplication::translate("Help", "e[xit]", 0));
        label_abandonExample->setText(QApplication::translate("Help", "abandon 23_3", 0));
        label_robustExample->setText(QApplication::translate("Help", "robust?", 0));
        label_periodicStatus->setText(QApplication::translate("Help", "To toggle periodic status......................................", 0));
        label_thaw->setText(QApplication::translate("Help", "To thaw engine....................................................", 0));
        label_p2Misc->setText(QApplication::translate("Help", "(p2 == put cfdp_ground 24 89)", 0));
        label_summaryExample->setText(QApplication::translate("Help", "sum[mary]", 0));
        label_mibExample->setText(QApplication::translate("Help", "mib", 0));
        label_sim->setText(QApplication::translate("Help", "To set link simulator mode (example)..................", 0));
        label_classMinus->setText(QApplication::translate("Help", "To disable a class of messages (example)...........", 0));
        label_cancelExample->setText(QApplication::translate("Help", "cancel 23_2", 0));
        label_getExample->setText(QApplication::translate("Help", "get ack_limit", 0));
        label_thawExample->setText(QApplication::translate("Help", "t[haw]", 0));
        label_resetTotals->setText(QApplication::translate("Help", "To reset statistical totals......................................", 0));
        label_classPlus->setText(QApplication::translate("Help", "To enable a class of messages (example)............", 0));
        label_updateExample->setText(QApplication::translate("Help", "update 50", 0));
        label_transStatusExample->setText(QApplication::translate("Help", "v", 0));
        label_p1Misc->setText(QApplication::translate("Help", "(p1 == put cfdp_flight 24 88)", 0));
        label_resumeExample->setText(QApplication::translate("Help", "resume 23_1", 0));
        label_robust->setText(QApplication::translate("Help", "To test engine robustness....................................", 0));
        label_report->setText(QApplication::translate("Help", "To report a transaction (example).......................", 0));
        label_cancel->setText(QApplication::translate("Help", "To cancel a transaction (example).......................", 0));
        label_update->setText(QApplication::translate("Help", "To set cycles between updates (example)...........", 0));
        label_classMinusExample->setText(QApplication::translate("Help", "class- indications", 0));
        label_disableExample->setText(QApplication::translate("Help", "di[sable_messages]", 0));
        label_resetTotalsExample->setText(QApplication::translate("Help", "reset_totals", 0));
        label_classPlusExample->setText(QApplication::translate("Help", "class+ all", 0));
        label_putExample->setText(QApplication::translate("Help", "put -class2 data.in 24 data.out", 0));
        label_freezeExample->setText(QApplication::translate("Help", "f[reeze]", 0));
        label_help->setText(QApplication::translate("Help", "To see a list of available commands....................", 0));
        label_exit->setText(QApplication::translate("Help", "To disconnect.......................................................", 0));
        label_helpExample->setText(QApplication::translate("Help", "h[elp]", 0));
        label_numberMisc->setText(QApplication::translate("Help", "(50 == sim success_rate=50)", 0));
        label_put->setText(QApplication::translate("Help", "To put a transaction (example)............................", 0));
        label_echoExample->setText(QApplication::translate("Help", "echo", 0));
        label_echo->setText(QApplication::translate("Help", "To toggle echo.....................................................", 0));
        label_setExample->setText(QApplication::translate("Help", "set nak_limit 10", 0));
        label_set->setText(QApplication::translate("Help", "To set MIB parameter (example)..........................", 0));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
