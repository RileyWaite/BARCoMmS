/********************************************************************************
** Form generated from reading UI file 'setter.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTER_H
#define UI_SETTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Setter
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox_ACKTimeout;
    QLabel *label_ACKTimeout;
    QLabel *label_EOFRecv;
    QLabel *label_NAKTimeout;
    QSpinBox *spinBox_NAKLimit;
    QLabel *label_resumed;
    QLabel *label_transFin;
    QLabel *label_ID;
    QComboBox *comboBox_fileRecv;
    QLabel *label_fileRecv;
    QComboBox *comboBox_EOFSent;
    QComboBox *comboBox_suspended;
    QComboBox *comboBox_EOFRecv;
    QComboBox *comboBox_transFin;
    QComboBox *comboBox_save;
    QLabel *label_suspended;
    QSpinBox *spinBox_chunkSize;
    QLabel *label_NAKLimit;
    QLabel *label_EOFSent;
    QLabel *label_inactivity;
    QComboBox *comboBox_ID;
    QLabel *label_fileSent;
    QLabel *label_save;
    QSpinBox *spinBox_ACKLimit;
    QComboBox *comboBox_resumed;
    QLabel *label_chunkSize;
    QLabel *label_ACKLimit;
    QSpinBox *spinBox_NAKTimeout;
    QSpinBox *spinBox_inactivity;
    QComboBox *comboBox_fileSent;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;

    void setupUi(QDialog *Setter)
    {
        if (Setter->objectName().isEmpty())
            Setter->setObjectName(QStringLiteral("Setter"));
        Setter->resize(501, 701);
        Setter->setMinimumSize(QSize(501, 701));
        Setter->setMaximumSize(QSize(501, 701));
        buttonBox = new QDialogButtonBox(Setter);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-10, 640, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBox_ACKTimeout = new QSpinBox(Setter);
        spinBox_ACKTimeout->setObjectName(QStringLiteral("spinBox_ACKTimeout"));
        spinBox_ACKTimeout->setGeometry(QRect(360, 440, 111, 22));
        spinBox_ACKTimeout->setMaximum(999999999);
        spinBox_ACKTimeout->setValue(5);
        label_ACKTimeout = new QLabel(Setter);
        label_ACKTimeout->setObjectName(QStringLiteral("label_ACKTimeout"));
        label_ACKTimeout->setGeometry(QRect(20, 440, 321, 16));
        label_EOFRecv = new QLabel(Setter);
        label_EOFRecv->setObjectName(QStringLiteral("label_EOFRecv"));
        label_EOFRecv->setGeometry(QRect(20, 200, 321, 16));
        label_NAKTimeout = new QLabel(Setter);
        label_NAKTimeout->setObjectName(QStringLiteral("label_NAKTimeout"));
        label_NAKTimeout->setGeometry(QRect(20, 500, 321, 16));
        spinBox_NAKLimit = new QSpinBox(Setter);
        spinBox_NAKLimit->setObjectName(QStringLiteral("spinBox_NAKLimit"));
        spinBox_NAKLimit->setGeometry(QRect(360, 470, 111, 22));
        spinBox_NAKLimit->setMaximum(999999999);
        spinBox_NAKLimit->setValue(25);
        label_resumed = new QLabel(Setter);
        label_resumed->setObjectName(QStringLiteral("label_resumed"));
        label_resumed->setGeometry(QRect(20, 290, 321, 16));
        label_transFin = new QLabel(Setter);
        label_transFin->setObjectName(QStringLiteral("label_transFin"));
        label_transFin->setGeometry(QRect(20, 350, 321, 16));
        label_ID = new QLabel(Setter);
        label_ID->setObjectName(QStringLiteral("label_ID"));
        label_ID->setGeometry(QRect(20, 590, 321, 16));
        comboBox_fileRecv = new QComboBox(Setter);
        comboBox_fileRecv->setObjectName(QStringLiteral("comboBox_fileRecv"));
        comboBox_fileRecv->setGeometry(QRect(360, 260, 111, 22));
        label_fileRecv = new QLabel(Setter);
        label_fileRecv->setObjectName(QStringLiteral("label_fileRecv"));
        label_fileRecv->setGeometry(QRect(20, 260, 321, 16));
        comboBox_EOFSent = new QComboBox(Setter);
        comboBox_EOFSent->setObjectName(QStringLiteral("comboBox_EOFSent"));
        comboBox_EOFSent->setGeometry(QRect(360, 170, 111, 22));
        comboBox_suspended = new QComboBox(Setter);
        comboBox_suspended->setObjectName(QStringLiteral("comboBox_suspended"));
        comboBox_suspended->setGeometry(QRect(360, 320, 111, 22));
        comboBox_EOFRecv = new QComboBox(Setter);
        comboBox_EOFRecv->setObjectName(QStringLiteral("comboBox_EOFRecv"));
        comboBox_EOFRecv->setGeometry(QRect(360, 200, 111, 22));
        comboBox_transFin = new QComboBox(Setter);
        comboBox_transFin->setObjectName(QStringLiteral("comboBox_transFin"));
        comboBox_transFin->setGeometry(QRect(360, 350, 111, 22));
        comboBox_save = new QComboBox(Setter);
        comboBox_save->setObjectName(QStringLiteral("comboBox_save"));
        comboBox_save->setGeometry(QRect(360, 380, 111, 22));
        label_suspended = new QLabel(Setter);
        label_suspended->setObjectName(QStringLiteral("label_suspended"));
        label_suspended->setGeometry(QRect(20, 320, 321, 16));
        spinBox_chunkSize = new QSpinBox(Setter);
        spinBox_chunkSize->setObjectName(QStringLiteral("spinBox_chunkSize"));
        spinBox_chunkSize->setGeometry(QRect(360, 560, 111, 22));
        spinBox_chunkSize->setMinimum(4);
        spinBox_chunkSize->setMaximum(65200);
        spinBox_chunkSize->setSingleStep(4);
        spinBox_chunkSize->setValue(65200);
        label_NAKLimit = new QLabel(Setter);
        label_NAKLimit->setObjectName(QStringLiteral("label_NAKLimit"));
        label_NAKLimit->setGeometry(QRect(20, 470, 321, 16));
        label_EOFSent = new QLabel(Setter);
        label_EOFSent->setObjectName(QStringLiteral("label_EOFSent"));
        label_EOFSent->setGeometry(QRect(20, 170, 321, 16));
        label_inactivity = new QLabel(Setter);
        label_inactivity->setObjectName(QStringLiteral("label_inactivity"));
        label_inactivity->setGeometry(QRect(20, 530, 321, 16));
        comboBox_ID = new QComboBox(Setter);
        comboBox_ID->setObjectName(QStringLiteral("comboBox_ID"));
        comboBox_ID->setGeometry(QRect(360, 590, 111, 22));
        label_fileSent = new QLabel(Setter);
        label_fileSent->setObjectName(QStringLiteral("label_fileSent"));
        label_fileSent->setGeometry(QRect(20, 230, 321, 16));
        label_save = new QLabel(Setter);
        label_save->setObjectName(QStringLiteral("label_save"));
        label_save->setGeometry(QRect(20, 380, 321, 16));
        spinBox_ACKLimit = new QSpinBox(Setter);
        spinBox_ACKLimit->setObjectName(QStringLiteral("spinBox_ACKLimit"));
        spinBox_ACKLimit->setGeometry(QRect(360, 410, 111, 22));
        spinBox_ACKLimit->setMaximum(999999999);
        spinBox_ACKLimit->setValue(25);
        comboBox_resumed = new QComboBox(Setter);
        comboBox_resumed->setObjectName(QStringLiteral("comboBox_resumed"));
        comboBox_resumed->setGeometry(QRect(360, 290, 111, 22));
        label_chunkSize = new QLabel(Setter);
        label_chunkSize->setObjectName(QStringLiteral("label_chunkSize"));
        label_chunkSize->setGeometry(QRect(20, 560, 321, 16));
        label_ACKLimit = new QLabel(Setter);
        label_ACKLimit->setObjectName(QStringLiteral("label_ACKLimit"));
        label_ACKLimit->setGeometry(QRect(20, 410, 321, 16));
        spinBox_NAKTimeout = new QSpinBox(Setter);
        spinBox_NAKTimeout->setObjectName(QStringLiteral("spinBox_NAKTimeout"));
        spinBox_NAKTimeout->setGeometry(QRect(360, 500, 111, 22));
        spinBox_NAKTimeout->setMaximum(999999999);
        spinBox_NAKTimeout->setValue(5);
        spinBox_inactivity = new QSpinBox(Setter);
        spinBox_inactivity->setObjectName(QStringLiteral("spinBox_inactivity"));
        spinBox_inactivity->setGeometry(QRect(360, 530, 111, 22));
        spinBox_inactivity->setMaximum(999999999);
        spinBox_inactivity->setSingleStep(100);
        spinBox_inactivity->setValue(86400);
        comboBox_fileSent = new QComboBox(Setter);
        comboBox_fileSent->setObjectName(QStringLiteral("comboBox_fileSent"));
        comboBox_fileSent->setGeometry(QRect(360, 230, 111, 22));
        groupBox_description = new QGroupBox(Setter);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 451, 131));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        QWidget::setTabOrder(comboBox_EOFSent, comboBox_EOFRecv);
        QWidget::setTabOrder(comboBox_EOFRecv, comboBox_fileSent);
        QWidget::setTabOrder(comboBox_fileSent, comboBox_fileRecv);
        QWidget::setTabOrder(comboBox_fileRecv, comboBox_resumed);
        QWidget::setTabOrder(comboBox_resumed, comboBox_suspended);
        QWidget::setTabOrder(comboBox_suspended, comboBox_transFin);
        QWidget::setTabOrder(comboBox_transFin, comboBox_save);
        QWidget::setTabOrder(comboBox_save, spinBox_ACKLimit);
        QWidget::setTabOrder(spinBox_ACKLimit, spinBox_ACKTimeout);
        QWidget::setTabOrder(spinBox_ACKTimeout, spinBox_NAKLimit);
        QWidget::setTabOrder(spinBox_NAKLimit, spinBox_NAKTimeout);
        QWidget::setTabOrder(spinBox_NAKTimeout, spinBox_inactivity);
        QWidget::setTabOrder(spinBox_inactivity, spinBox_chunkSize);
        QWidget::setTabOrder(spinBox_chunkSize, comboBox_ID);

        retranslateUi(Setter);
        QObject::connect(buttonBox, SIGNAL(accepted()), Setter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Setter, SLOT(reject()));

        QMetaObject::connectSlotsByName(Setter);
    } // setupUi

    void retranslateUi(QDialog *Setter)
    {
        Setter->setWindowTitle(QApplication::translate("Setter", "MIB Settings", 0));
        label_ACKTimeout->setText(QApplication::translate("Setter", "ACK Timeout", 0));
        label_EOFRecv->setText(QApplication::translate("Setter", "Issue EOF-Received Indication?", 0));
        label_NAKTimeout->setText(QApplication::translate("Setter", "NAK Timeout", 0));
        label_resumed->setText(QApplication::translate("Setter", "Issue Resumed Indication?", 0));
        label_transFin->setText(QApplication::translate("Setter", "Issue Transaction-Finished Indication?", 0));
        label_ID->setText(QApplication::translate("Setter", "Node ID", 0));
        label_fileRecv->setText(QApplication::translate("Setter", "Issue File-Segment-Received Indication?", 0));
        label_suspended->setText(QApplication::translate("Setter", "Issue Suspended Indication?", 0));
        label_NAKLimit->setText(QApplication::translate("Setter", "NAK Limit", 0));
        label_EOFSent->setText(QApplication::translate("Setter", "Issue EOF-Sent Indication?", 0));
        label_inactivity->setText(QApplication::translate("Setter", "Inactivity Timeout", 0));
        label_fileSent->setText(QApplication::translate("Setter", "Issue File-Segment-Sent Indication?", 0));
        label_save->setText(QApplication::translate("Setter", "Save Incomplete Files?", 0));
        label_chunkSize->setText(QApplication::translate("Setter", "Outgoing File Chunk Size (Bytes)", 0));
        label_ACKLimit->setText(QApplication::translate("Setter", "ACK Limit", 0));
        groupBox_description->setTitle(QApplication::translate("Setter", "Description", 0));
        label_description->setText(QApplication::translate("Setter", "The Management Information Base (MIB) contains such\n"
"information as default values for user communications\n"
"requirements (e.g., for address mapping, and for\n"
"communication timer settings).", 0));
    } // retranslateUi

};

namespace Ui {
    class Setter: public Ui_Setter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTER_H
