/********************************************************************************
** Form generated from reading UI file 'barcomms_camera.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARCOMMS_CAMERA_H
#define UI_BARCOMMS_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../src/modules/BARCoMmS_Camera/glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_BARCoMmS_Camera
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QLabel *label_3;
    QSlider *brightnessSlider;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QSlider *contrastSlider;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QSlider *pictureSlider;
    QPushButton *changeDirectory;
    QPushButton *openImage;
    QVBoxLayout *verticalLayout_6;
    GLWidget *mainImage;
    QLabel *timeStamp;
    QLabel *numberOfImagesInDirectory;

    void setupUi(QMainWindow *BARCoMmS_Camera)
    {
        if (BARCoMmS_Camera->objectName().isEmpty())
            BARCoMmS_Camera->setObjectName(QStringLiteral("BARCoMmS_Camera"));
        BARCoMmS_Camera->resize(1054, 480);
        centralWidget = new QWidget(BARCoMmS_Camera);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_7 = new QVBoxLayout(centralWidget);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        redSlider = new QSlider(centralWidget);
        redSlider->setObjectName(QStringLiteral("redSlider"));
        redSlider->setMaximumSize(QSize(25, 16777215));
        redSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(redSlider);

        greenSlider = new QSlider(centralWidget);
        greenSlider->setObjectName(QStringLiteral("greenSlider"));
        greenSlider->setMaximumSize(QSize(25, 16777215));
        greenSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(greenSlider);

        blueSlider = new QSlider(centralWidget);
        blueSlider->setObjectName(QStringLiteral("blueSlider"));
        blueSlider->setMaximumSize(QSize(25, 16777215));
        blueSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(blueSlider);


        verticalLayout->addLayout(horizontalLayout);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(140, 16777215));

        verticalLayout->addWidget(label_3);

        brightnessSlider = new QSlider(centralWidget);
        brightnessSlider->setObjectName(QStringLiteral("brightnessSlider"));
        brightnessSlider->setMaximumSize(QSize(140, 16777215));
        brightnessSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(brightnessSlider);


        verticalLayout_5->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(140, 16777215));

        verticalLayout_2->addWidget(label_2);

        contrastSlider = new QSlider(centralWidget);
        contrastSlider->setObjectName(QStringLiteral("contrastSlider"));
        contrastSlider->setMaximumSize(QSize(140, 16777215));
        contrastSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(contrastSlider);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(140, 16777215));

        verticalLayout_3->addWidget(label_4);

        pictureSlider = new QSlider(centralWidget);
        pictureSlider->setObjectName(QStringLiteral("pictureSlider"));
        pictureSlider->setMaximumSize(QSize(140, 16777215));
        pictureSlider->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(pictureSlider);


        verticalLayout_4->addLayout(verticalLayout_3);

        changeDirectory = new QPushButton(centralWidget);
        changeDirectory->setObjectName(QStringLiteral("changeDirectory"));

        verticalLayout_4->addWidget(changeDirectory);

        openImage = new QPushButton(centralWidget);
        openImage->setObjectName(QStringLiteral("openImage"));

        verticalLayout_4->addWidget(openImage);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        mainImage = new GLWidget(centralWidget);
        mainImage->setObjectName(QStringLiteral("mainImage"));
        mainImage->setMinimumSize(QSize(0, 0));
        mainImage->setBaseSize(QSize(0, 0));

        verticalLayout_6->addWidget(mainImage);

        timeStamp = new QLabel(centralWidget);
        timeStamp->setObjectName(QStringLiteral("timeStamp"));
        timeStamp->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(timeStamp);

        numberOfImagesInDirectory = new QLabel(centralWidget);
        numberOfImagesInDirectory->setObjectName(QStringLiteral("numberOfImagesInDirectory"));
        numberOfImagesInDirectory->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(numberOfImagesInDirectory);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_7->addLayout(horizontalLayout_2);

        BARCoMmS_Camera->setCentralWidget(centralWidget);

        retranslateUi(BARCoMmS_Camera);

        QMetaObject::connectSlotsByName(BARCoMmS_Camera);
    } // setupUi

    void retranslateUi(QMainWindow *BARCoMmS_Camera)
    {
        BARCoMmS_Camera->setWindowTitle(QApplication::translate("BARCoMmS_Camera", "Camera - BARCoMmS", 0));
        label->setText(QApplication::translate("BARCoMmS_Camera", "<html><head/><body><p align=\"center\">Color</p><p align=\"center\"><span style=\" color:#e80000;\">R</span><span style=\" color:#ffffff;\">_____</span><span style=\" color:#17a707;\">G</span><span style=\" color:#ffffff;\">_____</span><span style=\" color:#0b28cb;\">B</span></p></body></html>", 0));
        label_3->setText(QApplication::translate("BARCoMmS_Camera", "<html><head/><body><p align=\"center\">Brightness</p></body></html>", 0));
        label_2->setText(QApplication::translate("BARCoMmS_Camera", "<html><head/><body><p align=\"center\">Contrast</p></body></html>", 0));
        label_4->setText(QApplication::translate("BARCoMmS_Camera", "<html><head/><body><p align=\"center\">Previous Pictures</p></body></html>", 0));
        changeDirectory->setText(QApplication::translate("BARCoMmS_Camera", "Change File Path", 0));
        openImage->setText(QApplication::translate("BARCoMmS_Camera", "Open Image", 0));
        timeStamp->setText(QApplication::translate("BARCoMmS_Camera", "TextLabel", 0));
        numberOfImagesInDirectory->setText(QApplication::translate("BARCoMmS_Camera", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class BARCoMmS_Camera: public Ui_BARCoMmS_Camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARCOMMS_CAMERA_H
