/********************************************************************************
** Form generated from reading UI file 'sorting.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTING_H
#define UI_SORTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sorting
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *timeButton;
    QRadioButton *sizeButton;
    QRadioButton *commandButton;
    QRadioButton *statusButton;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *timeButton2;
    QRadioButton *sizeButton2;
    QRadioButton *commandButton2;
    QRadioButton *statusButton2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Sorting)
    {
        if (Sorting->objectName().isEmpty())
            Sorting->setObjectName(QStringLiteral("Sorting"));
        Sorting->resize(769, 152);
        layoutWidget = new QWidget(Sorting);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 751, 132));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        timeButton = new QRadioButton(layoutWidget);
        timeButton->setObjectName(QStringLiteral("timeButton"));

        verticalLayout->addWidget(timeButton);

        sizeButton = new QRadioButton(layoutWidget);
        sizeButton->setObjectName(QStringLiteral("sizeButton"));

        verticalLayout->addWidget(sizeButton);

        commandButton = new QRadioButton(layoutWidget);
        commandButton->setObjectName(QStringLiteral("commandButton"));

        verticalLayout->addWidget(commandButton);

        statusButton = new QRadioButton(layoutWidget);
        statusButton->setObjectName(QStringLiteral("statusButton"));

        verticalLayout->addWidget(statusButton);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        timeButton2 = new QRadioButton(layoutWidget);
        timeButton2->setObjectName(QStringLiteral("timeButton2"));

        verticalLayout_3->addWidget(timeButton2);

        sizeButton2 = new QRadioButton(layoutWidget);
        sizeButton2->setObjectName(QStringLiteral("sizeButton2"));

        verticalLayout_3->addWidget(sizeButton2);

        commandButton2 = new QRadioButton(layoutWidget);
        commandButton2->setObjectName(QStringLiteral("commandButton2"));

        verticalLayout_3->addWidget(commandButton2);

        statusButton2 = new QRadioButton(layoutWidget);
        statusButton2->setObjectName(QStringLiteral("statusButton2"));

        verticalLayout_3->addWidget(statusButton2);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(Sorting);
        QObject::connect(buttonBox, SIGNAL(accepted()), Sorting, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Sorting, SLOT(reject()));

        QMetaObject::connectSlotsByName(Sorting);
    } // setupUi

    void retranslateUi(QDialog *Sorting)
    {
        Sorting->setWindowTitle(QApplication::translate("Sorting", "Sort Options", 0));
        timeButton->setText(QApplication::translate("Sorting", "Chronological (Oldest first)", 0));
        sizeButton->setText(QApplication::translate("Sorting", "File Size (CFDP only) (Smallest first)", 0));
        commandButton->setText(QApplication::translate("Sorting", "Command (FSW only) (Lowest APID first)", 0));
        statusButton->setText(QApplication::translate("Sorting", "Status (Successful, Unsuccessful, In Progress)", 0));
        timeButton2->setText(QApplication::translate("Sorting", "Chronological (Newest first)", 0));
        sizeButton2->setText(QApplication::translate("Sorting", "File Size (CFDP only) (Largest first)", 0));
        commandButton2->setText(QApplication::translate("Sorting", "Command (FSW only) (Highest APID first)", 0));
        statusButton2->setText(QApplication::translate("Sorting", "Status (In Progress, Unsuccessful, Successful", 0));
    } // retranslateUi

};

namespace Ui {
    class Sorting: public Ui_Sorting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTING_H
