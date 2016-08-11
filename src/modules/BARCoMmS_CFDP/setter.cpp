#include "setter.h"
#include "ui_setter.h"

#include <fstream>
#include <sstream>

// Constructor
Setter::Setter(QWidget *parent) : QDialog(parent), ui(new Ui::Setter){
    ui->setupUi(this);

    ui->comboBox_EOFSent->addItem("Yes");
    ui->comboBox_EOFSent->addItem("No");

    ui->comboBox_EOFRecv->addItem("Yes");
    ui->comboBox_EOFRecv->addItem("No");

    ui->comboBox_fileSent->addItem("Yes");
    ui->comboBox_fileSent->addItem("No");

    ui->comboBox_fileRecv->addItem("Yes");
    ui->comboBox_fileRecv->addItem("No");

    ui->comboBox_save->addItem("Yes");
    ui->comboBox_save->addItem("No");

    ui->comboBox_resumed->addItem("Yes");
    ui->comboBox_resumed->addItem("No");

    ui->comboBox_suspended->addItem("Yes");
    ui->comboBox_suspended->addItem("No");

    ui->comboBox_transFin->addItem("Yes");
    ui->comboBox_transFin->addItem("No");

    initNodesList();
}

// Destructor
Setter::~Setter(){
    delete ui;
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP what the new 'MIB' parameters' values are
void Setter::on_buttonBox_accepted(){
    MIB mib;

    strcpy(mib.ID, ui->comboBox_ID->currentText().toStdString().c_str());
    if(!strcmp(mib.ID, "Error")) strcpy(mib.ID, global_mib.ID);
    strcpy(mib.EOFRecv, ui->comboBox_EOFRecv->currentText().toStdString().c_str());
    strcpy(mib.EOFSent, ui->comboBox_EOFSent->currentText().toStdString().c_str());
    strcpy(mib.fileRecv, ui->comboBox_fileRecv->currentText().toStdString().c_str());
    strcpy(mib.fileSent, ui->comboBox_fileSent->currentText().toStdString().c_str());
    strcpy(mib.resumed, ui->comboBox_resumed->currentText().toStdString().c_str());
    strcpy(mib.save, ui->comboBox_save->currentText().toStdString().c_str());
    strcpy(mib.suspended, ui->comboBox_suspended->currentText().toStdString().c_str());
    strcpy(mib.transFin, ui->comboBox_transFin->currentText().toStdString().c_str());
    mib.ACKLimit = ui->spinBox_ACKLimit->text().toUInt();
    mib.ACKTimeout = ui->spinBox_ACKTimeout->text().toUInt();
    mib.chunkSize = ui->spinBox_chunkSize->text().toUInt();
    mib.inactivity = ui->spinBox_inactivity->text().toUInt();
    mib.NAKLimit = ui->spinBox_NAKLimit->text().toUInt();
    mib.NAKTimeout = ui->spinBox_NAKTimeout->text().toUInt();

    emit setter_appendOutput(mib);
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void Setter::setter_changeLoadVals(){
    ui->comboBox_ID->setCurrentText(global_mib.ID);
    ui->comboBox_EOFRecv->setCurrentText(global_mib.EOFRecv);
    ui->comboBox_EOFSent->setCurrentText(global_mib.EOFSent);
    ui->comboBox_fileRecv->setCurrentText(global_mib.fileRecv);
    ui->comboBox_fileSent->setCurrentText(global_mib.fileSent);
    ui->comboBox_resumed->setCurrentText(global_mib.resumed);
    ui->comboBox_save->setCurrentText(global_mib.save);
    ui->comboBox_suspended->setCurrentText(global_mib.suspended);
    ui->comboBox_transFin->setCurrentText(global_mib.transFin);
    ui->spinBox_ACKLimit->setValue(global_mib.ACKLimit);
    ui->spinBox_ACKTimeout->setValue(global_mib.ACKTimeout);
    ui->spinBox_chunkSize->setValue(global_mib.chunkSize);
    ui->spinBox_inactivity->setValue(global_mib.inactivity);
    ui->spinBox_NAKLimit->setValue(global_mib.NAKLimit);
    ui->spinBox_NAKTimeout->setValue(global_mib.NAKTimeout);
}

// Load in all available nodes from mib.nodes into comboBox_ID
void Setter::initNodesList(){
    std::string line;
    std::ifstream fin("src/dependencies/CFDP/CODE/mib.nodes");

    // Ensure file opened properly
    if(!fin.is_open()){
        ui->comboBox_ID->addItem(global_mib.ID);
        ui->comboBox_ID->addItem("Error");
        return;
    }
    else{
        while(std::getline(fin, line)){
            std::istringstream strStream(line);
            float node;

            while(strStream >> node){
                ui->comboBox_ID->addItem(QString::number(node));
            }
        }

        // Close file
        fin.close();
    }
}
