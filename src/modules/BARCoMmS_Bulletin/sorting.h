#ifndef SORTING_H
#define SORTING_H

#include <QDialog>
#include <QObject>
#include <QPushButton>

namespace Ui {
class Sorting;
}

class Sorting : public QDialog
{
    Q_OBJECT

public:
    explicit Sorting(QWidget *parent = 0);
    ~Sorting();

public slots:

    //Emits signal to BC_Bulletin to sort tree items in chronological order (oldest first)
    void time();

    //Emits signal to BC_Bulletin to sort tree items in chronological order (newest first)
    void time2();

    //Emits signal to BC_Bulletin to sort tree items by file size (CFDP only) (smallest first)
    void size();

    //Emits signal to BC_Bulletin to sort tree items by file size (CFDP only) (largest first)
    void size2();

    //Emits signal to BC_Bulletin to sort tree items by command (FSW only) (lowest APID first)
    void command();

    //Emits signal to BC_Bulletin to sort tree items by command (FSW only) (highest APID first)
    void command2();

    //Emits signal to BC_Bulletin to sort tree items by status (Successful, unsuccessful, in progress)
    void status();

    //Emits signal to BC_Bulletin to sort tree items by status (In progress, unsuccessful, successful)
    void status2();

signals:

    //Notifies BC_Bulletin of field to sort by
    void chosen(int sortOption);

private:
    Ui::Sorting *ui;

};

#endif // SORTING_H
