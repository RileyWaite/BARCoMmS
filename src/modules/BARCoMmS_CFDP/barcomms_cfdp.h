#ifndef BARCOMMS_CFDP_H
#define BARCOMMS_CFDP_H

#include "classmessages.h"
#include "sim.h"
#include "updatecycles.h"
#include "setter.h"
#include "buffer.h"
#include "requests.h"
#include "help.h"
#include "options.h"
#include "worker.h"
#include "cfdpstructs.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>

namespace Ui{
    class BARCoMmS_CFDP;
}

class BARCoMmS_CFDP : public QMainWindow{
    Q_OBJECT

    public:
        // Constructor
        explicit BARCoMmS_CFDP(QWidget *parent = 0);

        // Destructor
        ~BARCoMmS_CFDP();

        // For exiting the BARCoMmS CFDP module
        void closeEvent(QCloseEvent *event);

    private:
        // For processing CFDP transactions in the background
        void startWorkInAThread();
        void cycleTransactions();
        void givePDU(DATA pdu);

        // For initializing windows used by BARCoMmS_CFDP
        void initWindow(QDialog *window);

        // For creating windows used by BARCoMmS_CFDP
        void createWindows();

        // For writing strings to Command_output
        void barcommsprint(std::string str);

        // For connecting all signals/slots
        void establishConnections();

        // For displaying BARCoMmS logo
        void showLogo(QString logo);

        // For initializing logFile
        void initLogFile(std::string);

        // For initializing all 'non-CFDP' variables
        void initVariables();

        Ui::BARCoMmS_CFDP *ui;

        // Worker thread for processing CFDP transactions
        Worker *workerThread;

        // For windows used by BARCoMmS_CFDP
        ClassMessages *classMessagesSender;
        Sim *simSender;
        Buffer *bufferSender;
        Options *optionsSender;
        UpdateCycles *updateCyclesSender;
        Setter *setterSender;
        Requests *requestsSender;
        Help *helpSender;

        // For log file
        std::string logFile;
        std::ofstream fout;

    private slots:
        void updateCycles_toggleUpdates();

        void on_pushButton_put_clicked();

        void on_pushButton_suspend_clicked();

        void on_pushButton_abandon_clicked();

        void on_pushButton_cancel_clicked();

        void on_pushButton_resume_clicked();

        void on_pushButton_report_clicked();

        void on_pushButton_detailedStatus_clicked();

        void on_pushButton_exit_clicked();

        void on_pushButton_classMessages_clicked();

        void on_pushButton_echo_clicked();

        void on_pushButton_sim_clicked();

        void on_pushButton_robust_clicked();

        void on_pushButton_resetTotals_clicked();

        void on_pushButton_help_clicked();

        void on_pushButton_setter_clicked();

        void on_pushButton_list_clicked();

        void on_pushButton_summary_clicked();

        void on_pushButton_transStatus_clicked();

        void on_lineEdit_input_returnPressed();

        void on_plainTextEdit_output_textChanged();

        void on_action_setBufferSize_triggered();

        void on_action_clearScreen_triggered();

        void on_action_options_triggered();

        void on_action_exit_triggered();

        void on_action_commands_triggered();

        void on_action_logEvents_toggled(bool checked);

        void output_changeLabel(char *str);

        void requests_changeLabel(std::vector<std::string> requests);

        void buffer_changeBuffer(unsigned int bufferSize);

        void updateCycles_changeLabel(unsigned int updateRate);

        void sim_changeLabel(LinkSim linkSim);

        void options_changeOptions(QString transType, QString recvID, QString destination);

        void classMessages_changeLabel(MessageClasses messageClasses);

        void setter_changeLabel(MIB mib);

        void on_pushButton_periodicStatus_toggled(bool depressed);

        void on_pushButton_freeze_toggled(bool depressed);

        void on_pushButton_disableEngineMessages_toggled(bool depressed);

    signals:
        // For communication with BARCoMmS_Bulletin
        void toBulletin(char *);

        // For terminating worker thread
        void terminator();
};

#endif // BARCOMMS_CFDP_H
