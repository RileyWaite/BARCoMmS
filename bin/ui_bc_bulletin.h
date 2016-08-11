/********************************************************************************
** Form generated from reading UI file 'bc_bulletin.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BC_BULLETIN_H
#define UI_BC_BULLETIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BC_Bulletin
{
public:
    QWidget *centralWidget;
    QTreeWidget *tx;
    QLabel *logo;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QProgressBar *progressBar;
    QLineEdit *searchBar;
    QTreeWidget *fsw;

    void setupUi(QMainWindow *BC_Bulletin)
    {
        if (BC_Bulletin->objectName().isEmpty())
            BC_Bulletin->setObjectName(QStringLiteral("BC_Bulletin"));
        BC_Bulletin->resize(1220, 521);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BC_Bulletin->sizePolicy().hasHeightForWidth());
        BC_Bulletin->setSizePolicy(sizePolicy);
        BC_Bulletin->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(BC_Bulletin);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tx = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tx->setHeaderItem(__qtreewidgetitem);
        tx->setObjectName(QStringLiteral("tx"));
        tx->setGeometry(QRect(10, 10, 811, 411));
        tx->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        tx->setExpandsOnDoubleClick(true);
        logo = new QLabel(centralWidget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(1000, 430, 211, 67));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 430, 971, 81));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(layoutWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        progressBar = new QProgressBar(layoutWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        horizontalLayout->addWidget(progressBar);

        searchBar = new QLineEdit(layoutWidget);
        searchBar->setObjectName(QStringLiteral("searchBar"));

        horizontalLayout->addWidget(searchBar);


        verticalLayout->addLayout(horizontalLayout);

        fsw = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        fsw->setHeaderItem(__qtreewidgetitem1);
        fsw->setObjectName(QStringLiteral("fsw"));
        fsw->setGeometry(QRect(830, 10, 381, 411));
        BC_Bulletin->setCentralWidget(centralWidget);

        retranslateUi(BC_Bulletin);

        QMetaObject::connectSlotsByName(BC_Bulletin);
    } // setupUi

    void retranslateUi(QMainWindow *BC_Bulletin)
    {
        BC_Bulletin->setWindowTitle(QApplication::translate("BC_Bulletin", "Bulletin - BARCoMmS", 0));
        logo->setText(QString());
        pushButton->setText(QApplication::translate("BC_Bulletin", "Expand All", 0));
        pushButton_2->setText(QApplication::translate("BC_Bulletin", "Collapse All", 0));
        pushButton_3->setText(QApplication::translate("BC_Bulletin", "Auto-Scroll", 0));
        pushButton_4->setText(QApplication::translate("BC_Bulletin", "Auto-Expand", 0));
        pushButton_5->setText(QApplication::translate("BC_Bulletin", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class BC_Bulletin: public Ui_BC_Bulletin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BC_BULLETIN_H
