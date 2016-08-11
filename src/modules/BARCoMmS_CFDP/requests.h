#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>

namespace Ui{
    class Requests;
}

class Requests : public QDialog{
    Q_OBJECT

    public:
        explicit Requests(QWidget *parent = 0);

        ~Requests();

        void initializeForm(QString title, QString description, QString request);

    private:
        std::vector<std::string> listTransactions();

        void clearForm();

        void outputToCommand();

        Ui::Requests *ui;

        // For dynamically created checkboxes
        QVBoxLayout *layout;
        QWidget *holder;

        // For storing transaction information
        std::vector<std::string> tempTransactions;

        // For storing the request type (eg. resume, suspend, or cancel)
        QString request;

        // For storing all checkboxes (boxen, get it? like, plural for box. If ox -> oxen, then box -> boxen? :D)
        std::vector<QCheckBox*> boxen;

    private slots:
        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

        void clicked();

    signals:
        void requests_appendOutput(std::vector<std::string> requests);
};

#endif // REQUESTS_H
