/********************************************************************************
** Form generated from reading UI file 'camera_capture_img_window.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_CAPTURE_IMG_WINDOW_H
#define UI_CAMERA_CAPTURE_IMG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera_Capture_Img_Window
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *avgBrightnessLabel;
    QSlider *avgBrightnessEdit;
    QLabel *fillLabel;
    QSlider *fillEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Camera_Capture_Img_Window)
    {
        if (Camera_Capture_Img_Window->objectName().isEmpty())
            Camera_Capture_Img_Window->setObjectName(QStringLiteral("Camera_Capture_Img_Window"));
        Camera_Capture_Img_Window->resize(323, 110);
        widget = new QWidget(Camera_Capture_Img_Window);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(21, 20, 281, 68));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        avgBrightnessLabel = new QLabel(widget);
        avgBrightnessLabel->setObjectName(QStringLiteral("avgBrightnessLabel"));

        gridLayout->addWidget(avgBrightnessLabel, 0, 0, 1, 1);

        avgBrightnessEdit = new QSlider(widget);
        avgBrightnessEdit->setObjectName(QStringLiteral("avgBrightnessEdit"));
        avgBrightnessEdit->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(avgBrightnessEdit, 0, 1, 1, 1);

        fillLabel = new QLabel(widget);
        fillLabel->setObjectName(QStringLiteral("fillLabel"));

        gridLayout->addWidget(fillLabel, 1, 0, 1, 1);

        fillEdit = new QSlider(widget);
        fillEdit->setObjectName(QStringLiteral("fillEdit"));
        fillEdit->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(fillEdit, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        buttonBox->raise();
        avgBrightnessLabel->raise();
        fillLabel->raise();
        avgBrightnessEdit->raise();
        fillEdit->raise();
        avgBrightnessLabel->raise();
        avgBrightnessEdit->raise();
        fillEdit->raise();

        retranslateUi(Camera_Capture_Img_Window);
        QObject::connect(buttonBox, SIGNAL(accepted()), Camera_Capture_Img_Window, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Camera_Capture_Img_Window, SLOT(reject()));

        QMetaObject::connectSlotsByName(Camera_Capture_Img_Window);
    } // setupUi

    void retranslateUi(QDialog *Camera_Capture_Img_Window)
    {
        Camera_Capture_Img_Window->setWindowTitle(QApplication::translate("Camera_Capture_Img_Window", "Capture Camera Image", 0));
        avgBrightnessLabel->setText(QApplication::translate("Camera_Capture_Img_Window", "Exposure", 0));
        fillLabel->setText(QApplication::translate("Camera_Capture_Img_Window", "Fill", 0));
    } // retranslateUi

};

namespace Ui {
    class Camera_Capture_Img_Window: public Ui_Camera_Capture_Img_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_CAPTURE_IMG_WINDOW_H
