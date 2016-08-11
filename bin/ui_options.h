/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;
    QLabel *label_transType;
    QLabel *label_recvID;
    QLabel *label_destination;
    QPushButton *pushButton_destination;
    QComboBox *comboBox_transType;
    QComboBox *comboBox_recvID;
    QLineEdit *lineEdit_destination;

    void setupUi(QDialog *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(521, 331);
        Options->setMinimumSize(QSize(521, 331));
        Options->setMaximumSize(QSize(521, 331));
        buttonBox = new QDialogButtonBox(Options);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 270, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_description = new QGroupBox(Options);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 481, 101));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        label_transType = new QLabel(Options);
        label_transType->setObjectName(QStringLiteral("label_transType"));
        label_transType->setGeometry(QRect(20, 140, 151, 21));
        label_recvID = new QLabel(Options);
        label_recvID->setObjectName(QStringLiteral("label_recvID"));
        label_recvID->setGeometry(QRect(20, 180, 151, 21));
        label_destination = new QLabel(Options);
        label_destination->setObjectName(QStringLiteral("label_destination"));
        label_destination->setGeometry(QRect(20, 220, 151, 21));
        pushButton_destination = new QPushButton(Options);
        pushButton_destination->setObjectName(QStringLiteral("pushButton_destination"));
        pushButton_destination->setGeometry(QRect(400, 220, 101, 21));
        comboBox_transType = new QComboBox(Options);
        comboBox_transType->setObjectName(QStringLiteral("comboBox_transType"));
        comboBox_transType->setGeometry(QRect(400, 140, 101, 22));
        comboBox_recvID = new QComboBox(Options);
        comboBox_recvID->setObjectName(QStringLiteral("comboBox_recvID"));
        comboBox_recvID->setGeometry(QRect(400, 180, 101, 22));
        lineEdit_destination = new QLineEdit(Options);
        lineEdit_destination->setObjectName(QStringLiteral("lineEdit_destination"));
        lineEdit_destination->setGeometry(QRect(180, 220, 221, 22));
        QWidget::setTabOrder(comboBox_transType, comboBox_recvID);
        QWidget::setTabOrder(comboBox_recvID, pushButton_destination);
        QWidget::setTabOrder(pushButton_destination, lineEdit_destination);

        retranslateUi(Options);
        QObject::connect(buttonBox, SIGNAL(accepted()), Options, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Options, SLOT(reject()));

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QDialog *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", 0));
        groupBox_description->setTitle(QApplication::translate("Options", "Description", 0));
        label_description->setText(QApplication::translate("Options", "Options are available for setting the transfer type, client,\n"
"and file destination for use with the \"Put\" command.", 0));
        label_transType->setText(QApplication::translate("Options", "Transfer Type", 0));
        label_recvID->setText(QApplication::translate("Options", "Receiver's Entity ID", 0));
        label_destination->setText(QApplication::translate("Options", "File Destination", 0));
        pushButton_destination->setText(QApplication::translate("Options", "Browse", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
