#ifndef LEGEND_H
#define LEGEND_H

#include <QDialog>
#include <QPixmap>
#include <QPalette>

namespace Ui {
class legend;
}

class legend : public QDialog
{
    Q_OBJECT

public:
    explicit legend(QWidget *parent = 0);
    ~legend();

private:
    Ui::legend *ui;
};

#endif // LEGEND_H
