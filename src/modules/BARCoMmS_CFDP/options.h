#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui{
    class Options;
}

class Options : public QDialog{
    Q_OBJECT

    public:
        explicit Options(QWidget *parent = 0);

        ~Options();

        void options_changeLoadVals();

        // For parameters pertaining to the receiver
        QString transType;
        QString recvID;
        QString destination;

    private:
        void initNodesList();

        Ui::Options *ui;

    private slots:
        void on_buttonBox_accepted();

        void on_pushButton_destination_clicked();

        void on_lineEdit_destination_textChanged(const QString &text);

    signals:
        void options_modifyOptions(QString transType, QString recvID, QString destination);
};

#endif // OPTIONS_H
