/********************************************************************************
** Form generated from reading UI file 'buffer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUFFER_H
#define UI_BUFFER_H

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

class Ui_Buffer
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;
    QLabel *label_bufferSize;
    QSpinBox *spinBox_bufferSize;

    void setupUi(QDialog *Buffer)
    {
        if (Buffer->objectName().isEmpty())
            Buffer->setObjectName(QStringLiteral("Buffer"));
        Buffer->resize(441, 241);
        Buffer->setMinimumSize(QSize(441, 241));
        Buffer->setMaximumSize(QSize(441, 241));
        buttonBox = new QDialogButtonBox(Buffer);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-40, 180, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_description = new QGroupBox(Buffer);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 401, 101));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        label_bufferSize = new QLabel(Buffer);
        label_bufferSize->setObjectName(QStringLiteral("label_bufferSize"));
        label_bufferSize->setGeometry(QRect(100, 140, 111, 21));
        spinBox_bufferSize = new QSpinBox(Buffer);
        spinBox_bufferSize->setObjectName(QStringLiteral("spinBox_bufferSize"));
        spinBox_bufferSize->setGeometry(QRect(250, 140, 111, 22));
        spinBox_bufferSize->setMaximum(999999999);
        spinBox_bufferSize->setSingleStep(5);
        spinBox_bufferSize->setValue(500);

        retranslateUi(Buffer);
        QObject::connect(buttonBox, SIGNAL(accepted()), Buffer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Buffer, SLOT(reject()));

        QMetaObject::connectSlotsByName(Buffer);
    } // setupUi

    void retranslateUi(QDialog *Buffer)
    {
        Buffer->setWindowTitle(QApplication::translate("Buffer", "Set Buffer Size", 0));
        groupBox_description->setTitle(QApplication::translate("Buffer", "Description", 0));
        label_description->setText(QApplication::translate("Buffer", "Sets the size of the buffer for the output terminal\n"
"in the Command window. Enter 0 for an unlimited\n"
"buffer size.", 0));
        label_bufferSize->setText(QApplication::translate("Buffer", "Buffer Size", 0));
    } // retranslateUi

};

namespace Ui {
    class Buffer: public Ui_Buffer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUFFER_H
