#include "bc_ditl_legend.h"
#include "bc_ditl_constants.cpp"

#include "ui_legend.h"

legend::legend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::legend)
{
    ui->setupUi(this);
    this->setModal(false);
    QPixmap bkgnd(QString::fromStdString(RESOURCE_LOCATION).append("Legend.PNG"));
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;

    flags = flags & (~helpFlag);
    setWindowFlags(flags);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

legend::~legend()
{
    delete ui;
}
