#ifndef WORKER_H
#define WORKER_H

#include "../dependencies/CFDP/CODE/cfdp_code.h"

#include <QObject>
#include <QThread>

class Worker : public QThread{
    Q_OBJECT

    private:
        void run() Q_DECL_OVERRIDE;

        bool end;

    signals:
        void readyToCycleTransactions();

        void readyToGivePDU(DATA pdu);

    public slots:
        void terminate();
};

#endif // WORKER_H
