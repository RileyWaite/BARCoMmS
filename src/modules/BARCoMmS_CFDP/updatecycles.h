#ifndef UPDATECYCLES_H
#define UPDATECYCLES_H

#include <QDialog>

namespace Ui{
    class UpdateCycles;
}

class UpdateCycles : public QDialog{
    Q_OBJECT

    public:
        explicit UpdateCycles(QWidget *parent = 0);

        ~UpdateCycles();

        void updateCycles_changeLoadVals();

        void displayStatus();

        // For periodic status updates
        unsigned int updateRate;
        bool periodicStatus;
        unsigned int cycle;

    private:
        Ui::UpdateCycles *ui;

    private slots:
        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

    signals:
        void updateCycles_appendOutput(unsigned int updateRate);

        void updateCycles_toggle();
};

#endif // UPDATECYCLES_H
