#ifndef CLASSMESSAGES_H
#define CLASSMESSAGES_H

#include "cfdpstructs.h"

#include <QDialog>

namespace Ui{
    class ClassMessages;
}

class ClassMessages : public QDialog{
    Q_OBJECT

    public:
        explicit ClassMessages(QWidget *parent = 0);

        ~ClassMessages();

        void classMessages_changeLoadVals();

    private:
        Ui::ClassMessages *ui;

    private slots:
        void on_buttonBox_accepted();

        void on_checkBox_all_toggled(bool checked);

        void checker();

        void on_checkBox_indications_toggled();

        void on_checkBox_debugMemoryUse_toggled();

        void on_checkBox_debugNAK_toggled();

        void on_checkBox_debugPDU_toggled();

        void on_checkBox_PDUFiledata_toggled();

        void on_checkBox_PDUNonFiledata_toggled();

        void on_checkBox_PDURetransmittedFD_toggled();

        void on_checkBox_stateAll_toggled();

        void on_checkBox_stateChange_toggled();

    signals:
        void classMessages_appendOutput(MessageClasses messageClasses);
};

#endif // CLASSMESSAGES_H
