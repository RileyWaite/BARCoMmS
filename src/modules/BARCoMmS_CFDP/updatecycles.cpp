#include "updatecycles.h"
#include "ui_updatecycles.h"
#include "cfdpstructs.h"
#include "../dependencies/CFDP/CODE/cfdp_code.h"

// Constructor
UpdateCycles::UpdateCycles(QWidget *parent) : QDialog(parent), ui(new Ui::UpdateCycles){
    ui->setupUi(this);

    this->updateRate = 200;
    this->periodicStatus = 0;
    this->cycle = 0;
}

// Destructor
UpdateCycles::~UpdateCycles(){
    delete ui;
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP what the new 'Periodic Status Updates' parameters' values are
void UpdateCycles::on_buttonBox_accepted(){
    unsigned int updateRate = ui->spinBox_updateRate->text().toUInt();

    this->periodicStatus ^= 1;

    emit updateCycles_appendOutput(updateRate);
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void UpdateCycles::updateCycles_changeLoadVals(){
    ui->spinBox_updateRate->setValue(this->updateRate);
}

// Emit a signal to BARCoMmS_CFDP to toggle the 'Periodic Status Updates' button back to its original state
void UpdateCycles::on_buttonBox_rejected(){
    emit updateCycles_toggle();
}

// Periodically show every transaction's status
void UpdateCycles::displayStatus(){
    if(this->periodicStatus){
        this->cycle++;
        if(this->cycle >= this->updateRate){
            m__show_transactions_status();
            this->cycle = 0;
        }
    }
}
