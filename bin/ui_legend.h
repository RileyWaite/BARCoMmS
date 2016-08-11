/********************************************************************************
** Form generated from reading UI file 'legend.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEGEND_H
#define UI_LEGEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_legend
{
public:

    void setupUi(QDialog *legend)
    {
        if (legend->objectName().isEmpty())
            legend->setObjectName(QStringLiteral("legend"));
        legend->resize(339, 292);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(legend->sizePolicy().hasHeightForWidth());
        legend->setSizePolicy(sizePolicy);
        legend->setMinimumSize(QSize(339, 292));
        legend->setMaximumSize(QSize(339, 292));

        retranslateUi(legend);

        QMetaObject::connectSlotsByName(legend);
    } // setupUi

    void retranslateUi(QDialog *legend)
    {
        legend->setWindowTitle(QApplication::translate("legend", "Legend", 0));
    } // retranslateUi

};

namespace Ui {
    class legend: public Ui_legend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEGEND_H
