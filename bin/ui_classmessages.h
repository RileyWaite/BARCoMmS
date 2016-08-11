/********************************************************************************
** Form generated from reading UI file 'classmessages.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLASSMESSAGES_H
#define UI_CLASSMESSAGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ClassMessages
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;
    QGroupBox *groupBox_options;
    QCheckBox *checkBox_all;
    QCheckBox *checkBox_indications;
    QCheckBox *checkBox_debugMemoryUse;
    QCheckBox *checkBox_debugPDU;
    QCheckBox *checkBox_debugNAK;
    QCheckBox *checkBox_PDUFiledata;
    QCheckBox *checkBox_PDURetransmittedFD;
    QCheckBox *checkBox_PDUNonFiledata;
    QCheckBox *checkBox_stateAll;
    QCheckBox *checkBox_stateChange;

    void setupUi(QDialog *ClassMessages)
    {
        if (ClassMessages->objectName().isEmpty())
            ClassMessages->setObjectName(QStringLiteral("ClassMessages"));
        ClassMessages->resize(291, 581);
        ClassMessages->setMinimumSize(QSize(291, 581));
        ClassMessages->setMaximumSize(QSize(291, 581));
        buttonBox = new QDialogButtonBox(ClassMessages);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-110, 520, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_description = new QGroupBox(ClassMessages);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 251, 141));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        groupBox_options = new QGroupBox(ClassMessages);
        groupBox_options->setObjectName(QStringLiteral("groupBox_options"));
        groupBox_options->setGeometry(QRect(20, 170, 251, 331));
        checkBox_all = new QCheckBox(groupBox_options);
        checkBox_all->setObjectName(QStringLiteral("checkBox_all"));
        checkBox_all->setGeometry(QRect(10, 30, 211, 20));
        checkBox_all->setChecked(false);
        checkBox_indications = new QCheckBox(groupBox_options);
        checkBox_indications->setObjectName(QStringLiteral("checkBox_indications"));
        checkBox_indications->setGeometry(QRect(10, 60, 211, 20));
        checkBox_indications->setChecked(true);
        checkBox_debugMemoryUse = new QCheckBox(groupBox_options);
        checkBox_debugMemoryUse->setObjectName(QStringLiteral("checkBox_debugMemoryUse"));
        checkBox_debugMemoryUse->setGeometry(QRect(10, 90, 211, 20));
        checkBox_debugMemoryUse->setChecked(false);
        checkBox_debugPDU = new QCheckBox(groupBox_options);
        checkBox_debugPDU->setObjectName(QStringLiteral("checkBox_debugPDU"));
        checkBox_debugPDU->setGeometry(QRect(10, 150, 211, 20));
        checkBox_debugPDU->setChecked(false);
        checkBox_debugNAK = new QCheckBox(groupBox_options);
        checkBox_debugNAK->setObjectName(QStringLiteral("checkBox_debugNAK"));
        checkBox_debugNAK->setGeometry(QRect(10, 120, 211, 20));
        checkBox_debugNAK->setChecked(false);
        checkBox_PDUFiledata = new QCheckBox(groupBox_options);
        checkBox_PDUFiledata->setObjectName(QStringLiteral("checkBox_PDUFiledata"));
        checkBox_PDUFiledata->setGeometry(QRect(10, 180, 211, 20));
        checkBox_PDUFiledata->setChecked(false);
        checkBox_PDURetransmittedFD = new QCheckBox(groupBox_options);
        checkBox_PDURetransmittedFD->setObjectName(QStringLiteral("checkBox_PDURetransmittedFD"));
        checkBox_PDURetransmittedFD->setGeometry(QRect(10, 240, 211, 20));
        checkBox_PDURetransmittedFD->setChecked(false);
        checkBox_PDUNonFiledata = new QCheckBox(groupBox_options);
        checkBox_PDUNonFiledata->setObjectName(QStringLiteral("checkBox_PDUNonFiledata"));
        checkBox_PDUNonFiledata->setGeometry(QRect(10, 210, 211, 20));
        checkBox_PDUNonFiledata->setChecked(true);
        checkBox_stateAll = new QCheckBox(groupBox_options);
        checkBox_stateAll->setObjectName(QStringLiteral("checkBox_stateAll"));
        checkBox_stateAll->setGeometry(QRect(10, 270, 211, 20));
        checkBox_stateAll->setChecked(false);
        checkBox_stateChange = new QCheckBox(groupBox_options);
        checkBox_stateChange->setObjectName(QStringLiteral("checkBox_stateChange"));
        checkBox_stateChange->setGeometry(QRect(10, 300, 211, 20));
        checkBox_stateChange->setChecked(false);
        QWidget::setTabOrder(checkBox_all, checkBox_indications);
        QWidget::setTabOrder(checkBox_indications, checkBox_debugMemoryUse);
        QWidget::setTabOrder(checkBox_debugMemoryUse, checkBox_debugNAK);
        QWidget::setTabOrder(checkBox_debugNAK, checkBox_debugPDU);
        QWidget::setTabOrder(checkBox_debugPDU, checkBox_PDUFiledata);
        QWidget::setTabOrder(checkBox_PDUFiledata, checkBox_PDUNonFiledata);
        QWidget::setTabOrder(checkBox_PDUNonFiledata, checkBox_PDURetransmittedFD);
        QWidget::setTabOrder(checkBox_PDURetransmittedFD, checkBox_stateAll);
        QWidget::setTabOrder(checkBox_stateAll, checkBox_stateChange);

        retranslateUi(ClassMessages);
        QObject::connect(buttonBox, SIGNAL(accepted()), ClassMessages, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ClassMessages, SLOT(reject()));

        QMetaObject::connectSlotsByName(ClassMessages);
    } // setupUi

    void retranslateUi(QDialog *ClassMessages)
    {
        ClassMessages->setWindowTitle(QApplication::translate("ClassMessages", "Message Classes", 0));
        groupBox_description->setTitle(QApplication::translate("ClassMessages", "Description", 0));
        label_description->setText(QApplication::translate("ClassMessages", "Enable or disable\n"
"message-classes. Each class\n"
"of messages displays\n"
"information pertinent to\n"
"that class.", 0));
        groupBox_options->setTitle(QApplication::translate("ClassMessages", "Options", 0));
        checkBox_all->setText(QApplication::translate("ClassMessages", "All", 0));
        checkBox_indications->setText(QApplication::translate("ClassMessages", "Indications", 0));
        checkBox_debugMemoryUse->setText(QApplication::translate("ClassMessages", "Debug Memory Use", 0));
        checkBox_debugPDU->setText(QApplication::translate("ClassMessages", "Debug PDU", 0));
        checkBox_debugNAK->setText(QApplication::translate("ClassMessages", "Debug NAK", 0));
        checkBox_PDUFiledata->setText(QApplication::translate("ClassMessages", "PDU Filedata", 0));
        checkBox_PDURetransmittedFD->setText(QApplication::translate("ClassMessages", "PDU Retransmitted FD", 0));
        checkBox_PDUNonFiledata->setText(QApplication::translate("ClassMessages", "PDU Non-Filedata", 0));
        checkBox_stateAll->setText(QApplication::translate("ClassMessages", "State All", 0));
        checkBox_stateChange->setText(QApplication::translate("ClassMessages", "State Change", 0));
    } // retranslateUi

};

namespace Ui {
    class ClassMessages: public Ui_ClassMessages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLASSMESSAGES_H
