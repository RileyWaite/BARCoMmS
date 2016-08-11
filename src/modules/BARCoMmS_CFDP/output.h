#ifndef OUTPUT_H
#define OUTPUT_H

#include <QDialog>

class Output : public QObject{
    Q_OBJECT

    public:
        void printer(char *str);

    signals:
        void output_appendOutput(char *str);
};

extern Output *outputSender;

#endif // OUTPUT_H
