/********************************************************************************
** Form generated from reading UI file 'requests.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REQUESTS_H
#define UI_REQUESTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Requests
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout_2;
    QLabel *label_description;
    QGroupBox *groupBox_transactions;
    QGridLayout *gridLayout;
    QScrollArea *scrollArea_transactions;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QDialog *Requests)
    {
        if (Requests->objectName().isEmpty())
            Requests->setObjectName(QStringLiteral("Requests"));
        Requests->resize(251, 571);
        Requests->setMinimumSize(QSize(251, 571));
        Requests->setMaximumSize(QSize(251, 571));
        buttonBox = new QDialogButtonBox(Requests);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-130, 510, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_description = new QGroupBox(Requests);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 211, 121));
        gridLayout_2 = new QGridLayout(groupBox_description);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout_2->addWidget(label_description, 0, 0, 1, 1);

        groupBox_transactions = new QGroupBox(Requests);
        groupBox_transactions->setObjectName(QStringLiteral("groupBox_transactions"));
        groupBox_transactions->setGeometry(QRect(20, 150, 211, 341));
        gridLayout = new QGridLayout(groupBox_transactions);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea_transactions = new QScrollArea(groupBox_transactions);
        scrollArea_transactions->setObjectName(QStringLiteral("scrollArea_transactions"));
        scrollArea_transactions->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 203, 316));
        scrollArea_transactions->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea_transactions, 0, 0, 1, 1);


        retranslateUi(Requests);
        QObject::connect(buttonBox, SIGNAL(accepted()), Requests, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Requests, SLOT(reject()));

        QMetaObject::connectSlotsByName(Requests);
    } // setupUi

    void retranslateUi(QDialog *Requests)
    {
        Requests->setWindowTitle(QApplication::translate("Requests", "Request Error", 0));
        groupBox_description->setTitle(QApplication::translate("Requests", "Description", 0));
        label_description->setText(QApplication::translate("Requests", "Error loading request.", 0));
        groupBox_transactions->setTitle(QApplication::translate("Requests", "Transactions", 0));
    } // retranslateUi

};

namespace Ui {
    class Requests: public Ui_Requests {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REQUESTS_H
