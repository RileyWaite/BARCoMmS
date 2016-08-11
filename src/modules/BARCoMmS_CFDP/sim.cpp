#include "sim.h"
#include "ui_sim.h"

// Constructor
Sim::Sim(QWidget *parent) : QDialog(parent), ui(new Ui::Sim){
    ui->setupUi(this);
}

// Destructor
Sim::~Sim(){
    delete ui;
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP what the new 'Link Simulator' parameters' values are
void Sim::on_buttonBox_accepted(){
    LinkSim linkSim;
    linkSim.rate = ui->spinBox_rate->text().toUInt();
    linkSim.delay = ui->spinBox_delay->text().toUInt();

    // Set the mode
    if(ui->radioButton_normal->isChecked()){
        strcpy(linkSim.mode, "sim normal");
    }
    else if(ui->radioButton_duplicate->isChecked()){
        strcpy(linkSim.mode, "sim duplicate");
    }
    else if(ui->radioButton_reorder->isChecked()){
        strcpy(linkSim.mode, "sim reorder");
    }
    else if(ui->radioButton_dropAll->isChecked()){
        strcpy(linkSim.mode, "sim drop_all");
    }
    else if(ui->radioButton_dropAllACKAndFin->isChecked()){
        strcpy(linkSim.mode, "sim drop_all_ack_and_fin");
    }
    else if(ui->radioButton_dropAllFin->isChecked()){
        strcpy(linkSim.mode, "sim drop_all_fin");
    }
    else if(ui->radioButton_dropAllNAK->isChecked()){
        strcpy(linkSim.mode, "sim drop_all_nak");
    }
    else if(ui->radioButton_dropAllButEOF->isChecked()){
        strcpy(linkSim.mode, "sim drop_all_but_eof");
    }
    else if(ui->radioButton_dropAllButMD->isChecked()){
        strcpy(linkSim.mode, "sim drop_all_but_md");
    }
    else if(ui->radioButton_dropOneACKEOF->isChecked()){
        strcpy(linkSim.mode, "sim drop_one_ack_eof");
    }
    else if(ui->radioButton_dropOneACKFin->isChecked()){
        strcpy(linkSim.mode, "sim drop_one_ack_fin");
    }
    else if(ui->radioButton_dropOneEOF->isChecked()){
        strcpy(linkSim.mode, "sim drop_one_eof");
    }
    else if(ui->radioButton_dropOneFin->isChecked()){
        strcpy(linkSim.mode, "sim drop_one_fin");
    }
    else if(ui->radioButton_dropOneMD->isChecked()){
        strcpy(linkSim.mode, "sim drop_one_md");
    }

    // Set the corruption option
    if(ui->radioButton_corruptNone->isChecked()){
        strcpy(linkSim.corruption, "sim corrupt_none");
    }
    else if(ui->radioButton_corruptEOFChecksum->isChecked()){
        strcpy(linkSim.corruption, "sim corrupt_eof_checksum");
    }
    else if(ui->radioButton_corruptEOFFileSize->isChecked()){
        strcpy(linkSim.corruption, "sim corrupt_eof_file_size");
    }

    emit sim_appendOutput(linkSim);
}

// Changes the values loaded into the UI elements (eg. check boxes, combo boxes, and spin boxes)
void Sim::sim_changeLoadVals(){
    ui->spinBox_rate->setValue(global_linkSim.rate);
    ui->spinBox_delay->setValue(global_linkSim.delay);

    if(!strcmp(global_linkSim.mode, "sim normal")){
        ui->radioButton_normal->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim duplicate")){
        ui->radioButton_duplicate->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim reorder")){
        ui->radioButton_reorder->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all")){
        ui->radioButton_dropAll->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all_ack_and_fin")){
        ui->radioButton_dropAllACKAndFin->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all_fin")){
        ui->radioButton_dropAllFin->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all_nak")){
        ui->radioButton_dropAllNAK->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all_but_eof")){
        ui->radioButton_dropAllButEOF->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_all_but_md")){
        ui->radioButton_dropAllButMD->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_one_ack_eof")){
        ui->radioButton_dropOneACKEOF->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_one_ack_fin")){
        ui->radioButton_dropOneACKFin->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_one_eof")){
        ui->radioButton_dropOneEOF->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_one_fin")){
        ui->radioButton_dropOneFin->setChecked(1);
    }
    else if(!strcmp(global_linkSim.mode, "sim drop_one_md")){
        ui->radioButton_dropOneMD->setChecked(1);
    }

    // Load in corruption setting
    if(!strcmp(global_linkSim.corruption, "sim corrupt_none")){
        ui->radioButton_corruptNone->setChecked(1);
    }
    else if(!strcmp(global_linkSim.corruption, "sim corrupt_eof_checksum")){
        ui->radioButton_corruptEOFChecksum->setChecked(1);
    }
    else if(!strcmp(global_linkSim.corruption, "sim corrupt_eof_file_size")){
        ui->radioButton_corruptEOFFileSize->setChecked(1);
    }
}
