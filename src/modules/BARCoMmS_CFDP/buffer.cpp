#include "buffer.h"
#include "ui_buffer.h"

// Constructor
Buffer::Buffer(QWidget *parent) : QDialog(parent), ui(new Ui::Buffer){
    ui->setupUi(this);

    this->bufferSize = 500;
}

// Destructor
Buffer::~Buffer(){
    delete ui;
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP what the new 'Buffer Size' parameters' values are
void Buffer::on_buttonBox_accepted(){
    unsigned int bufferSize = ui->spinBox_bufferSize->text().toUInt();

    emit buffer_modifyBuffer(bufferSize);
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void Buffer::buffer_changeLoadVals(){
    ui->spinBox_bufferSize->setValue(this->bufferSize);
}
