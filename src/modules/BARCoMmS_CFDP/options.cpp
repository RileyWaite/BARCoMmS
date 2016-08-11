#include "options.h"
#include "ui_options.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>

// Constructor
Options::Options(QWidget *parent) : QDialog(parent), ui(new Ui::Options){
    ui->setupUi(this);

    ui->comboBox_transType->addItem("Class 1");
    ui->comboBox_transType->addItem("Class 2");

    ui->label_transType->setToolTip("\"Class 1\" provides for the unreliable delivery of bounded or unbounded data files from the source to the destination.\n"
                                              "\"Class 2\" provides for the reliable delivery of bounded or unbounded data files from the source to the destination.");
    ui->label_recvID->setToolTip("The CFDP protocol entity through which communication is to be established (files will be sent to this entity ID).");
    ui->label_destination->setToolTip("The file destination is where all \"Sent\" files will be delivered.");

    this->transType = "Class 2";
    this->recvID = "24";
    this->destination = "/home/ben/Desktop/testOut";

    initNodesList();
}

// Destructor
Options::~Options(){
    delete ui;
}

// Emits a signal to BARCoMms_CFDP that tells BARCoMmS_CFDP what the new 'Options' parameters' values are
void Options::on_buttonBox_accepted(){
    QString transType = ui->comboBox_transType->currentText();
    QString recvID = ui->comboBox_recvID->currentText();
    QString destination = ui->lineEdit_destination->text();

    emit options_modifyOptions(transType, recvID, destination);
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void Options::options_changeLoadVals(){
    ui->comboBox_transType->setCurrentText(this->transType);
    ui->comboBox_recvID->setCurrentText(this->recvID);
    ui->lineEdit_destination->setText(this->destination);
    ui->lineEdit_destination->setToolTip(ui->lineEdit_destination->text());
}

// Open folder dialog box for folder browsing
void Options::on_pushButton_destination_clicked(){
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Select a Folder"), ui->lineEdit_destination->text(), QFileDialog::ShowDirsOnly);

    if(!folderName.isEmpty()){
        ui->lineEdit_destination->setText(folderName);
        ui->lineEdit_destination->setToolTip(ui->lineEdit_destination->text());
    }
}

// Load in all available nodes from mib.nodes into comboBox_recvID
void Options::initNodesList(){
    std::string line;
    std::ifstream fin("src/dependencies/CFDP/CODE/mib.nodes");

    // Ensure file opened properly
    if(!fin.is_open()){
        ui->comboBox_recvID->addItem(this->recvID);
        ui->comboBox_recvID->addItem("Error");
        return;
    }
    else{
        while(std::getline(fin, line)){
            std::istringstream strStream(line);
            float node;

            while(strStream >> node){
                ui->comboBox_recvID->addItem(QString::number(node));
            }
        }

        // Close file
        fin.close();
    }
}

// Update tool tip to show current destination setting whenever text is changed
void Options::on_lineEdit_destination_textChanged(const QString &text){
    ui->lineEdit_destination->setToolTip(text);
}
