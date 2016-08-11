#include "ui_sorting.h"
#include "sorting.h"

Sorting::Sorting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sorting)
{
    ui->setupUi(this);

    //Set size of dialog window
    this->setFixedSize(769, 152);

    //Set text of push buttons
    ui->timeButton->setText("Chronological (Oldest first)");
    ui->timeButton2->setText("Chronological (Newest first)");
    ui->sizeButton->setText("File size (CFDP only) (Smallest first)");
    ui->sizeButton2->setText("File size(CFDP only) (Largest first)");
    ui->commandButton->setText("Command (FSW only) (Lowest APID first)");
    ui->commandButton2->setText("Command (FSW only) (Highest APID first)");
    ui->statusButton->setText("Status (Successful, unsuccessful, in progress)");
    ui->statusButton2->setText("Status (In progress, unsuccessful, successful)");

    //Connect push buttons to respective sorting option
    connect(ui->timeButton, SIGNAL(clicked()), this, SLOT(time()));
    connect(ui->timeButton2, SIGNAL(clicked()), this, SLOT(time2()));
    connect(ui->sizeButton, SIGNAL(clicked()), this, SLOT(size()));
    connect(ui->sizeButton2, SIGNAL(clicked()), this, SLOT(size2()));
    connect(ui->commandButton, SIGNAL(clicked()), this, SLOT(command()));
    connect(ui->commandButton2, SIGNAL(clicked()), this, SLOT(command2()));
    connect(ui->statusButton, SIGNAL(clicked()), this, SLOT(status()));
    connect(ui->statusButton2, SIGNAL(clicked()), this, SLOT(status2()));
}

Sorting::~Sorting()
{
    delete ui;
}

//Emits signal to BC_Bulletin to sort tree items in chronological order (oldest first)
void Sorting::time()
{
    emit chosen(0);
}

//Emits signal to BC_Bulletin to sort tree items in chronological order (newest first)
void Sorting::time2()
{
    emit chosen(1);
}

//Emits signal to BC_Bulletin to sort tree items by file size (CFDP only) (smallest first)
void Sorting::size()
{
    emit chosen(2);
}

//Emits signal to BC_Bulletin to sort tree items by file size (CFDP only) (largest first)
void Sorting::size2()
{
    emit chosen(3);
}

//Emits signal to BC_Bulletin to sort tree items by command (FSW only) (lowest APID first)
void Sorting::command()
{
    emit chosen(4);
}

//Emits signal to BC_Bulletin to sort tree items by command (FSW only) (highest APID first)
void Sorting::command2()
{
    emit chosen(5);
}

//Emits signal to BC_Bulletin to sort tree items by status (Successful, unsuccessful, in progress)
void Sorting::status()
{
    emit chosen(6);
}

//Emits signal to BC_Bulletin to sort tree items by status (In progress, unsuccessful, successful)
void Sorting::status2()
{
    emit chosen(7);
}
