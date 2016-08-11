/********************************************************************************
** Form generated from reading UI file 'sim.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIM_H
#define UI_SIM_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Sim
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_rate;
    QSpinBox *spinBox_rate;
    QGroupBox *groupBox_description;
    QGridLayout *gridLayout;
    QLabel *label_description;
    QLabel *label_delay;
    QSpinBox *spinBox_delay;
    QGroupBox *groupBox_modes;
    QRadioButton *radioButton_duplicate;
    QRadioButton *radioButton_reorder;
    QRadioButton *radioButton_dropAll;
    QRadioButton *radioButton_dropOneEOF;
    QRadioButton *radioButton_dropOneFin;
    QRadioButton *radioButton_normal;
    QRadioButton *radioButton_dropAllACKAndFin;
    QRadioButton *radioButton_dropAllFin;
    QRadioButton *radioButton_dropAllNAK;
    QRadioButton *radioButton_dropAllButEOF;
    QRadioButton *radioButton_dropAllButMD;
    QRadioButton *radioButton_dropOneMD;
    QRadioButton *radioButton_dropOneACKEOF;
    QRadioButton *radioButton_dropOneACKFin;
    QGroupBox *groupBox_corruptOptions;
    QRadioButton *radioButton_corruptNone;
    QRadioButton *radioButton_corruptEOFChecksum;
    QRadioButton *radioButton_corruptEOFFileSize;

    void setupUi(QDialog *Sim)
    {
        if (Sim->objectName().isEmpty())
            Sim->setObjectName(QStringLiteral("Sim"));
        Sim->resize(481, 771);
        Sim->setMinimumSize(QSize(481, 771));
        Sim->setMaximumSize(QSize(481, 771));
        buttonBox = new QDialogButtonBox(Sim);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-20, 720, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_rate = new QLabel(Sim);
        label_rate->setObjectName(QStringLiteral("label_rate"));
        label_rate->setGeometry(QRect(30, 180, 281, 21));
        spinBox_rate = new QSpinBox(Sim);
        spinBox_rate->setObjectName(QStringLiteral("spinBox_rate"));
        spinBox_rate->setGeometry(QRect(340, 180, 111, 22));
        spinBox_rate->setMaximum(100);
        spinBox_rate->setSingleStep(1);
        spinBox_rate->setValue(100);
        groupBox_description = new QGroupBox(Sim);
        groupBox_description->setObjectName(QStringLiteral("groupBox_description"));
        groupBox_description->setGeometry(QRect(20, 20, 441, 141));
        gridLayout = new QGridLayout(groupBox_description);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_description = new QLabel(groupBox_description);
        label_description->setObjectName(QStringLiteral("label_description"));

        gridLayout->addWidget(label_description, 0, 0, 1, 1);

        label_delay = new QLabel(Sim);
        label_delay->setObjectName(QStringLiteral("label_delay"));
        label_delay->setGeometry(QRect(30, 210, 281, 21));
        spinBox_delay = new QSpinBox(Sim);
        spinBox_delay->setObjectName(QStringLiteral("spinBox_delay"));
        spinBox_delay->setGeometry(QRect(340, 210, 111, 22));
        spinBox_delay->setMaximum(999999999);
        spinBox_delay->setSingleStep(1000);
        spinBox_delay->setValue(1000);
        groupBox_modes = new QGroupBox(Sim);
        groupBox_modes->setObjectName(QStringLiteral("groupBox_modes"));
        groupBox_modes->setGeometry(QRect(30, 250, 201, 451));
        radioButton_duplicate = new QRadioButton(groupBox_modes);
        radioButton_duplicate->setObjectName(QStringLiteral("radioButton_duplicate"));
        radioButton_duplicate->setGeometry(QRect(10, 60, 181, 20));
        radioButton_reorder = new QRadioButton(groupBox_modes);
        radioButton_reorder->setObjectName(QStringLiteral("radioButton_reorder"));
        radioButton_reorder->setGeometry(QRect(10, 90, 181, 20));
        radioButton_dropAll = new QRadioButton(groupBox_modes);
        radioButton_dropAll->setObjectName(QStringLiteral("radioButton_dropAll"));
        radioButton_dropAll->setGeometry(QRect(10, 120, 181, 20));
        radioButton_dropOneEOF = new QRadioButton(groupBox_modes);
        radioButton_dropOneEOF->setObjectName(QStringLiteral("radioButton_dropOneEOF"));
        radioButton_dropOneEOF->setGeometry(QRect(10, 360, 181, 20));
        radioButton_dropOneFin = new QRadioButton(groupBox_modes);
        radioButton_dropOneFin->setObjectName(QStringLiteral("radioButton_dropOneFin"));
        radioButton_dropOneFin->setGeometry(QRect(10, 390, 181, 20));
        radioButton_normal = new QRadioButton(groupBox_modes);
        radioButton_normal->setObjectName(QStringLiteral("radioButton_normal"));
        radioButton_normal->setGeometry(QRect(10, 30, 181, 20));
        radioButton_normal->setChecked(true);
        radioButton_dropAllACKAndFin = new QRadioButton(groupBox_modes);
        radioButton_dropAllACKAndFin->setObjectName(QStringLiteral("radioButton_dropAllACKAndFin"));
        radioButton_dropAllACKAndFin->setGeometry(QRect(10, 150, 181, 20));
        radioButton_dropAllFin = new QRadioButton(groupBox_modes);
        radioButton_dropAllFin->setObjectName(QStringLiteral("radioButton_dropAllFin"));
        radioButton_dropAllFin->setGeometry(QRect(10, 180, 181, 20));
        radioButton_dropAllNAK = new QRadioButton(groupBox_modes);
        radioButton_dropAllNAK->setObjectName(QStringLiteral("radioButton_dropAllNAK"));
        radioButton_dropAllNAK->setGeometry(QRect(10, 210, 181, 20));
        radioButton_dropAllButEOF = new QRadioButton(groupBox_modes);
        radioButton_dropAllButEOF->setObjectName(QStringLiteral("radioButton_dropAllButEOF"));
        radioButton_dropAllButEOF->setGeometry(QRect(10, 240, 181, 20));
        radioButton_dropAllButMD = new QRadioButton(groupBox_modes);
        radioButton_dropAllButMD->setObjectName(QStringLiteral("radioButton_dropAllButMD"));
        radioButton_dropAllButMD->setGeometry(QRect(10, 270, 181, 20));
        radioButton_dropOneMD = new QRadioButton(groupBox_modes);
        radioButton_dropOneMD->setObjectName(QStringLiteral("radioButton_dropOneMD"));
        radioButton_dropOneMD->setGeometry(QRect(10, 420, 181, 20));
        radioButton_dropOneACKEOF = new QRadioButton(groupBox_modes);
        radioButton_dropOneACKEOF->setObjectName(QStringLiteral("radioButton_dropOneACKEOF"));
        radioButton_dropOneACKEOF->setGeometry(QRect(10, 300, 181, 20));
        radioButton_dropOneACKFin = new QRadioButton(groupBox_modes);
        radioButton_dropOneACKFin->setObjectName(QStringLiteral("radioButton_dropOneACKFin"));
        radioButton_dropOneACKFin->setGeometry(QRect(10, 330, 181, 20));
        groupBox_corruptOptions = new QGroupBox(Sim);
        groupBox_corruptOptions->setObjectName(QStringLiteral("groupBox_corruptOptions"));
        groupBox_corruptOptions->setGeometry(QRect(250, 250, 201, 161));
        radioButton_corruptNone = new QRadioButton(groupBox_corruptOptions);
        radioButton_corruptNone->setObjectName(QStringLiteral("radioButton_corruptNone"));
        radioButton_corruptNone->setGeometry(QRect(10, 30, 181, 31));
        radioButton_corruptNone->setChecked(true);
        radioButton_corruptEOFChecksum = new QRadioButton(groupBox_corruptOptions);
        radioButton_corruptEOFChecksum->setObjectName(QStringLiteral("radioButton_corruptEOFChecksum"));
        radioButton_corruptEOFChecksum->setGeometry(QRect(10, 70, 181, 31));
        radioButton_corruptEOFFileSize = new QRadioButton(groupBox_corruptOptions);
        radioButton_corruptEOFFileSize->setObjectName(QStringLiteral("radioButton_corruptEOFFileSize"));
        radioButton_corruptEOFFileSize->setGeometry(QRect(10, 110, 181, 31));
        QWidget::setTabOrder(spinBox_rate, spinBox_delay);
        QWidget::setTabOrder(spinBox_delay, radioButton_normal);
        QWidget::setTabOrder(radioButton_normal, radioButton_duplicate);
        QWidget::setTabOrder(radioButton_duplicate, radioButton_reorder);
        QWidget::setTabOrder(radioButton_reorder, radioButton_dropAll);
        QWidget::setTabOrder(radioButton_dropAll, radioButton_dropAllACKAndFin);
        QWidget::setTabOrder(radioButton_dropAllACKAndFin, radioButton_dropAllFin);
        QWidget::setTabOrder(radioButton_dropAllFin, radioButton_dropAllNAK);
        QWidget::setTabOrder(radioButton_dropAllNAK, radioButton_dropAllButEOF);
        QWidget::setTabOrder(radioButton_dropAllButEOF, radioButton_dropAllButMD);
        QWidget::setTabOrder(radioButton_dropAllButMD, radioButton_dropOneACKEOF);
        QWidget::setTabOrder(radioButton_dropOneACKEOF, radioButton_dropOneACKFin);
        QWidget::setTabOrder(radioButton_dropOneACKFin, radioButton_dropOneEOF);
        QWidget::setTabOrder(radioButton_dropOneEOF, radioButton_dropOneFin);
        QWidget::setTabOrder(radioButton_dropOneFin, radioButton_dropOneMD);
        QWidget::setTabOrder(radioButton_dropOneMD, radioButton_corruptNone);
        QWidget::setTabOrder(radioButton_corruptNone, radioButton_corruptEOFChecksum);
        QWidget::setTabOrder(radioButton_corruptEOFChecksum, radioButton_corruptEOFFileSize);

        retranslateUi(Sim);
        QObject::connect(buttonBox, SIGNAL(accepted()), Sim, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Sim, SLOT(reject()));

        QMetaObject::connectSlotsByName(Sim);
    } // setupUi

    void retranslateUi(QDialog *Sim)
    {
        Sim->setWindowTitle(QApplication::translate("Sim", "Link Simulator", 0));
        label_rate->setText(QApplication::translate("Sim", "Link Simulator Success Rate (%)", 0));
        groupBox_description->setTitle(QApplication::translate("Sim", "Description", 0));
        label_description->setText(QApplication::translate("Sim", "The Link Simulator only affects outgoing PDUs. At any\n"
"given time, the Link Simulator can be in one particular\n"
"mode. The mode can be \"normal\", \"duplicate\",\n"
"\"reorder\", or one of the \"drop\" modes. For more\n"
"information, see User Guide 3.1 Appendix B.", 0));
        label_delay->setText(QApplication::translate("Sim", "Delay between PDUs (microseconds)", 0));
        groupBox_modes->setTitle(QApplication::translate("Sim", "Modes", 0));
        radioButton_duplicate->setText(QApplication::translate("Sim", "Duplicate", 0));
        radioButton_reorder->setText(QApplication::translate("Sim", "Reorder", 0));
        radioButton_dropAll->setText(QApplication::translate("Sim", "Drop All", 0));
        radioButton_dropOneEOF->setText(QApplication::translate("Sim", "Drop One EOF", 0));
        radioButton_dropOneFin->setText(QApplication::translate("Sim", "Drop One Fin", 0));
        radioButton_normal->setText(QApplication::translate("Sim", "Normal", 0));
        radioButton_dropAllACKAndFin->setText(QApplication::translate("Sim", "Drop All ACK And Fin", 0));
        radioButton_dropAllFin->setText(QApplication::translate("Sim", "Drop All Fin", 0));
        radioButton_dropAllNAK->setText(QApplication::translate("Sim", "Drop All NAK", 0));
        radioButton_dropAllButEOF->setText(QApplication::translate("Sim", "Drop All But EOF", 0));
        radioButton_dropAllButMD->setText(QApplication::translate("Sim", "Drop All But MD", 0));
        radioButton_dropOneMD->setText(QApplication::translate("Sim", "Drop One MD", 0));
        radioButton_dropOneACKEOF->setText(QApplication::translate("Sim", "Drop One ACK EOF", 0));
        radioButton_dropOneACKFin->setText(QApplication::translate("Sim", "Drop One ACK Fin", 0));
        groupBox_corruptOptions->setTitle(QApplication::translate("Sim", "Corrupt Options", 0));
        radioButton_corruptNone->setText(QApplication::translate("Sim", "Corrupt None", 0));
        radioButton_corruptEOFChecksum->setText(QApplication::translate("Sim", "Corrupt EOF\n"
"Checksum", 0));
        radioButton_corruptEOFFileSize->setText(QApplication::translate("Sim", "Corrupt EOF\n"
"File Size", 0));
    } // retranslateUi

};

namespace Ui {
    class Sim: public Ui_Sim {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIM_H
