#ifndef SETTER_H
#define SETTER_H

#include "cfdpstructs.h"

#include <QDialog>

namespace Ui{
    class Setter;
}

class Setter : public QDialog{
    Q_OBJECT

    public:
        explicit Setter(QWidget *parent = 0);

        ~Setter();

        void setter_changeLoadVals();

    private:
        void initNodesList();

        Ui::Setter *ui;

    private slots:
        void on_buttonBox_accepted();

    signals:
        void setter_appendOutput(MIB mib);
};

#endif // SETTER_H
