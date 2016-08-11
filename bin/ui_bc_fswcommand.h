/********************************************************************************
** Form generated from reading UI file 'bc_fswcommand.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BC_FSWCOMMAND_H
#define UI_BC_FSWCOMMAND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BC_FSWCommand
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *set_dev_avail;
    QPushButton *fsw_reboot;
    QPushButton *fsw_command;
    QPushButton *event_retrans;
    QPushButton *oper_mode;
    QPushButton *transmit_data_rate;
    QPushButton *download_image;
    QPushButton *telem_query;
    QPushButton *safe_mode;
    QPushButton *gnc;
    QPushButton *camera_capture_img;
    QPushButton *abort_comm_pass;
    QPushButton *prop_schedule;
    QLabel *logo;
    QPushButton *fsw_restart;
    QPushButton *reset_dev;
    QPushButton *comm_schedule;
    QPushButton *decom_enable;
    QPushButton *decom_commit;
    QPushButton *set_dev_power;
    QFrame *CommPass;
    QGridLayout *gridLayout_2;
    QFrame *frame_RSSI;
    QLabel *label_RSSI;
    QGraphicsView *gs_RSSI;
    QPushButton *but_DL;
    QPushButton *but_Ping;
    QLCDNumber *RSSI;

    void setupUi(QMainWindow *BC_FSWCommand)
    {
        if (BC_FSWCommand->objectName().isEmpty())
            BC_FSWCommand->setObjectName(QStringLiteral("BC_FSWCommand"));
        BC_FSWCommand->resize(595, 384);
        BC_FSWCommand->setMinimumSize(QSize(595, 0));
        centralwidget = new QWidget(BC_FSWCommand);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 554, 363));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        set_dev_avail = new QPushButton(layoutWidget);
        set_dev_avail->setObjectName(QStringLiteral("set_dev_avail"));

        gridLayout->addWidget(set_dev_avail, 1, 1, 1, 1);

        fsw_reboot = new QPushButton(layoutWidget);
        fsw_reboot->setObjectName(QStringLiteral("fsw_reboot"));

        gridLayout->addWidget(fsw_reboot, 5, 1, 1, 1);

        fsw_command = new QPushButton(layoutWidget);
        fsw_command->setObjectName(QStringLiteral("fsw_command"));

        gridLayout->addWidget(fsw_command, 0, 0, 1, 1);

        event_retrans = new QPushButton(layoutWidget);
        event_retrans->setObjectName(QStringLiteral("event_retrans"));

        gridLayout->addWidget(event_retrans, 7, 1, 1, 1);

        oper_mode = new QPushButton(layoutWidget);
        oper_mode->setObjectName(QStringLiteral("oper_mode"));

        gridLayout->addWidget(oper_mode, 8, 0, 1, 1);

        transmit_data_rate = new QPushButton(layoutWidget);
        transmit_data_rate->setObjectName(QStringLiteral("transmit_data_rate"));

        gridLayout->addWidget(transmit_data_rate, 6, 1, 1, 1);

        download_image = new QPushButton(layoutWidget);
        download_image->setObjectName(QStringLiteral("download_image"));

        gridLayout->addWidget(download_image, 0, 1, 1, 1);

        telem_query = new QPushButton(layoutWidget);
        telem_query->setObjectName(QStringLiteral("telem_query"));

        gridLayout->addWidget(telem_query, 2, 0, 1, 1);

        safe_mode = new QPushButton(layoutWidget);
        safe_mode->setObjectName(QStringLiteral("safe_mode"));

        gridLayout->addWidget(safe_mode, 7, 0, 1, 1);

        gnc = new QPushButton(layoutWidget);
        gnc->setObjectName(QStringLiteral("gnc"));

        gridLayout->addWidget(gnc, 3, 0, 1, 1);

        camera_capture_img = new QPushButton(layoutWidget);
        camera_capture_img->setObjectName(QStringLiteral("camera_capture_img"));

        gridLayout->addWidget(camera_capture_img, 10, 0, 1, 1);

        abort_comm_pass = new QPushButton(layoutWidget);
        abort_comm_pass->setObjectName(QStringLiteral("abort_comm_pass"));

        gridLayout->addWidget(abort_comm_pass, 9, 0, 1, 1);

        prop_schedule = new QPushButton(layoutWidget);
        prop_schedule->setObjectName(QStringLiteral("prop_schedule"));

        gridLayout->addWidget(prop_schedule, 6, 0, 1, 1);

        logo = new QLabel(layoutWidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setEnabled(true);

        gridLayout->addWidget(logo, 8, 1, 3, 1);

        fsw_restart = new QPushButton(layoutWidget);
        fsw_restart->setObjectName(QStringLiteral("fsw_restart"));

        gridLayout->addWidget(fsw_restart, 4, 1, 1, 1);

        reset_dev = new QPushButton(layoutWidget);
        reset_dev->setObjectName(QStringLiteral("reset_dev"));

        gridLayout->addWidget(reset_dev, 3, 1, 1, 1);

        comm_schedule = new QPushButton(layoutWidget);
        comm_schedule->setObjectName(QStringLiteral("comm_schedule"));

        gridLayout->addWidget(comm_schedule, 1, 0, 1, 1);

        decom_enable = new QPushButton(layoutWidget);
        decom_enable->setObjectName(QStringLiteral("decom_enable"));

        gridLayout->addWidget(decom_enable, 5, 0, 1, 1);

        decom_commit = new QPushButton(layoutWidget);
        decom_commit->setObjectName(QStringLiteral("decom_commit"));

        gridLayout->addWidget(decom_commit, 4, 0, 1, 1);

        set_dev_power = new QPushButton(layoutWidget);
        set_dev_power->setObjectName(QStringLiteral("set_dev_power"));

        gridLayout->addWidget(set_dev_power, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        CommPass = new QFrame(layoutWidget);
        CommPass->setObjectName(QStringLiteral("CommPass"));
        CommPass->setMinimumSize(QSize(0, 40));
        CommPass->setMaximumSize(QSize(16777215, 40));
        CommPass->setFrameShape(QFrame::NoFrame);
        CommPass->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(CommPass);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 1, 0, 1);
        frame_RSSI = new QFrame(CommPass);
        frame_RSSI->setObjectName(QStringLiteral("frame_RSSI"));
        frame_RSSI->setMaximumSize(QSize(133, 16777215));
        frame_RSSI->setFrameShape(QFrame::NoFrame);
        frame_RSSI->setFrameShadow(QFrame::Raised);
        label_RSSI = new QLabel(frame_RSSI);
        label_RSSI->setObjectName(QStringLiteral("label_RSSI"));
        label_RSSI->setGeometry(QRect(57, -5, 71, 51));
        label_RSSI->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        gs_RSSI = new QGraphicsView(frame_RSSI);
        gs_RSSI->setObjectName(QStringLiteral("gs_RSSI"));
        gs_RSSI->setGeometry(QRect(33, 3, 30, 30));
        gs_RSSI->setMaximumSize(QSize(50, 16777215));
        gs_RSSI->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(frame_RSSI, 0, 2, 2, 1);

        but_DL = new QPushButton(CommPass);
        but_DL->setObjectName(QStringLiteral("but_DL"));

        gridLayout_2->addWidget(but_DL, 0, 1, 2, 1);

        but_Ping = new QPushButton(CommPass);
        but_Ping->setObjectName(QStringLiteral("but_Ping"));

        gridLayout_2->addWidget(but_Ping, 0, 0, 2, 1);

        RSSI = new QLCDNumber(CommPass);
        RSSI->setObjectName(QStringLiteral("RSSI"));
        RSSI->setFrameShape(QFrame::NoFrame);
        RSSI->setDigitCount(2);

        gridLayout_2->addWidget(RSSI, 0, 3, 2, 1);


        verticalLayout->addWidget(CommPass);

        BC_FSWCommand->setCentralWidget(centralwidget);

        retranslateUi(BC_FSWCommand);

        QMetaObject::connectSlotsByName(BC_FSWCommand);
    } // setupUi

    void retranslateUi(QMainWindow *BC_FSWCommand)
    {
        BC_FSWCommand->setWindowTitle(QApplication::translate("BC_FSWCommand", "Command - BARCoMmS", 0));
        set_dev_avail->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        fsw_reboot->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        fsw_command->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        event_retrans->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        oper_mode->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        transmit_data_rate->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        download_image->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        telem_query->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        safe_mode->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        gnc->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        camera_capture_img->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        abort_comm_pass->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        prop_schedule->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        logo->setText(QString());
        fsw_restart->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        reset_dev->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        comm_schedule->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        decom_enable->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        decom_commit->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        set_dev_power->setText(QApplication::translate("BC_FSWCommand", "PushButton", 0));
        label_RSSI->setText(QApplication::translate("BC_FSWCommand", "Signal\n"
"Strength", 0));
        but_DL->setText(QApplication::translate("BC_FSWCommand", "Downlink", 0));
        but_Ping->setText(QApplication::translate("BC_FSWCommand", "Ping", 0));
    } // retranslateUi

};

namespace Ui {
    class BC_FSWCommand: public Ui_BC_FSWCommand {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BC_FSWCOMMAND_H
