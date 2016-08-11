#include "help.h"
#include "ui_help.h"

// Constructor
Help::Help(QWidget *parent) : QDialog(parent), ui(new Ui::Help){
    ui->setupUi(this);
}

// Destructor
Help::~Help(){
    delete ui;
}
