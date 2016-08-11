#ifndef BUFFER_H
#define BUFFER_H

#include <QDialog>

namespace Ui{
    class Buffer;
}

class Buffer : public QDialog{
    Q_OBJECT

    public:
        explicit Buffer(QWidget *parent = 0);

        ~Buffer();

        void buffer_changeLoadVals();

        // For setting the buffer size of plainTextEdit_output in the main window
        unsigned int bufferSize;

    private:
        Ui::Buffer *ui;

    private slots:
        void on_buttonBox_accepted();

    signals:
        void buffer_modifyBuffer(unsigned int bufferSize);
};

#endif // BUFFER_H
