/********************************************************************************
** Form generated from reading UI file 'camera_download_imgs_window.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_DOWNLOAD_IMGS_WINDOW_H
#define UI_CAMERA_DOWNLOAD_IMGS_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camera_Download_Imgs_Window
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *numImagesLabel;
    QSpinBox *numImagesEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Camera_Download_Imgs_Window)
    {
        if (Camera_Download_Imgs_Window->objectName().isEmpty())
            Camera_Download_Imgs_Window->setObjectName(QStringLiteral("Camera_Download_Imgs_Window"));
        Camera_Download_Imgs_Window->resize(408, 90);
        widget = new QWidget(Camera_Download_Imgs_Window);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 20, 371, 53));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        numImagesLabel = new QLabel(widget);
        numImagesLabel->setObjectName(QStringLiteral("numImagesLabel"));
        QFont font;
        font.setPointSize(12);
        numImagesLabel->setFont(font);

        gridLayout->addWidget(numImagesLabel, 0, 0, 1, 1);

        numImagesEdit = new QSpinBox(widget);
        numImagesEdit->setObjectName(QStringLiteral("numImagesEdit"));

        gridLayout->addWidget(numImagesEdit, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);

        buttonBox->raise();
        numImagesEdit->raise();
        numImagesLabel->raise();
        buttonBox->raise();

        retranslateUi(Camera_Download_Imgs_Window);
        QObject::connect(buttonBox, SIGNAL(accepted()), Camera_Download_Imgs_Window, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Camera_Download_Imgs_Window, SLOT(reject()));

        QMetaObject::connectSlotsByName(Camera_Download_Imgs_Window);
    } // setupUi

    void retranslateUi(QDialog *Camera_Download_Imgs_Window)
    {
        Camera_Download_Imgs_Window->setWindowTitle(QApplication::translate("Camera_Download_Imgs_Window", "Dialog", 0));
        numImagesLabel->setText(QApplication::translate("Camera_Download_Imgs_Window", "Number of images to download", 0));
    } // retranslateUi

};

namespace Ui {
    class Camera_Download_Imgs_Window: public Ui_Camera_Download_Imgs_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_DOWNLOAD_IMGS_WINDOW_H
