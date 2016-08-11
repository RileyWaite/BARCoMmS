/********************************************************************************
** Form generated from reading UI file 'updatecycles.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATECYCLES_H
#define UI_UPDATECYCLES_H

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
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_UpdateCycles
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;
    QLabel *label_updateRate;
    QSpinBox *spinBox_updateRate;

    void setupUi(QDialog *UpdateCycles)
    {
        if (UpdateCycles->objectName().isEmpty())
            UpdateCycles->setObjectName(QStringLiteral("UpdateCycles"));
        UpdateCycles->resize(441, 221);
        UpdateCycles->setMinimumSize(QSize(441, 221));
        UpdateCycles->setMaximumSize(QSize(441, 221));
        buttonBox = new QDialogButtonBox(UpdateCycles);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-40, 160, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_description = new QGroupBox(UpdateCycles);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 401, 81));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        label_updateRate = new QLabel(UpdateCycles);
        label_updateRate->setObjectName(QStringLiteral("label_updateRate"));
        label_updateRate->setGeometry(QRect(60, 120, 191, 21));
        spinBox_updateRate = new QSpinBox(UpdateCycles);
        spinBox_updateRate->setObjectName(QStringLiteral("spinBox_updateRate"));
        spinBox_updateRate->setGeometry(QRect(290, 120, 91, 22));
        spinBox_updateRate->setMaximum(999999999);
        spinBox_updateRate->setSingleStep(100);
        spinBox_updateRate->setValue(200);

        retranslateUi(UpdateCycles);
        QObject::connect(buttonBox, SIGNAL(accepted()), UpdateCycles, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), UpdateCycles, SLOT(reject()));

        QMetaObject::connectSlotsByName(UpdateCycles);
    } // setupUi

    void retranslateUi(QDialog *UpdateCycles)
    {
        UpdateCycles->setWindowTitle(QApplication::translate("UpdateCycles", "Periodic Status", 0));
        groupBox_description->setTitle(QApplication::translate("UpdateCycles", "Description", 0));
        label_description->setText(QApplication::translate("UpdateCycles", "Sets the number of cycles between each periodic\n"
"status update.", 0));
        label_updateRate->setText(QApplication::translate("UpdateCycles", "Cycles Between Updates", 0));
    } // retranslateUi

};

namespace Ui {
    class UpdateCycles: public Ui_UpdateCycles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATECYCLES_H
