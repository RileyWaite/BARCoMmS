#ifndef SIM_H
#define SIM_H

#include "cfdpstructs.h"

#include <QDialog>

namespace Ui{
    class Sim;
}

class Sim : public QDialog{
    Q_OBJECT

    public:
        explicit Sim(QWidget *parent = 0);

        ~Sim();

        void sim_changeLoadVals();

    private:
        Ui::Sim *ui;

    private slots:
        void on_buttonBox_accepted();

    signals:
        void sim_appendOutput(LinkSim sim);
};

#endif // SIM_H
