#include "requests.h"
#include "ui_requests.h"
#include "../dependencies/CFDP/CODE/cfdp_code.h"

// Constructor
Requests::Requests(QWidget *parent) : QDialog(parent), ui(new Ui::Requests){
    ui->setupUi(this);

    holder = new QWidget();
    layout = new QVBoxLayout(holder);
    layout->setAlignment(Qt::AlignTop);
    ui->scrollArea_transactions->setWidget(holder);
}

// Destructor
Requests::~Requests(){
    delete ui;
}

// Set the request type and acquire a list of current CFDP transactions and display them as checkboxes within the window
void Requests::initializeForm(QString title, QString description, QString request){
    setWindowTitle(title);
    ui->label_description->setText(description);
    this->request = request;

    // Generate the temporary transactions list for use in outputToCommand()
    this->tempTransactions = listTransactions();

    if(listTransactions().size() > 1){
        QCheckBox *allBox = new QCheckBox("All");
        allBox->setObjectName("All");
        allBox->setChecked(0);

        connect(allBox, SIGNAL(clicked(bool)), this, SLOT(clicked()));

        layout->addWidget(allBox);
        this->boxen.push_back(allBox);
    }
    for(unsigned short i = 0; i < listTransactions().size(); ++i){
        QCheckBox *dynamicBox = new QCheckBox(listTransactions()[i].c_str());
        dynamicBox->setObjectName(QString::fromStdString(listTransactions()[i]));
        dynamicBox->setChecked(0);

        connect(dynamicBox, SIGNAL(clicked(bool)), this, SLOT(clicked()));

        layout->addWidget(dynamicBox);
        this->boxen.push_back(dynamicBox);
    }
}

// Remove all checkboxes from the window and clear vector 'boxen'
void Requests::clearForm(){
    QLayoutItem* child;

    while(layout->count() != 0){
        child = layout->takeAt(0);
        if(child->widget() != 0){
            delete child->widget();
        }
    }

    this->boxen.clear();
}

// Emit a signal to BARCoMmS_CFDP that tells BARCoMmS_CFDP to print the commands associated with the request type and checked check boxes
void Requests::outputToCommand(){
    std::string str;
    std::vector<std::string> requests;

    for(unsigned short i = 0; i < this->boxen.size(); ++i){
        if(this->request != "detailed_status"){
            if(this->boxen.size() > 1 && i == 0 && this->boxen[i]->isChecked())
            {
                str = this->request.toStdString() + " all";
                requests.push_back(str);
                break;
            }
        }
        if(this->boxen.size() > 1 && i == 0){
            for(i = 1; i < this->boxen.size(); ++i){
                if(this->boxen[i]->isChecked()){
                    str = this->request.toStdString() + " " + tempTransactions[i-1];
                    requests.push_back(str);
                }
            }
            break;
        }
        for(i = 0; i < this->boxen.size(); ++i){
            if(this->boxen[i]->isChecked()){
                str = this->request.toStdString() + " " + tempTransactions[i];
                requests.push_back(str);
            }
        }
        break;
    }

    if(!requests.empty()) emit requests_appendOutput(requests);
}

void Requests::on_buttonBox_accepted(){
    outputToCommand();
    clearForm();
}

void Requests::on_buttonBox_rejected(){
    clearForm();
}

// Toggle which checkboxes should be checked depending on the status of the 'All' checkbox
void Requests::clicked(){
    //Handle the event in which 'All' is checked/unchecked
    QString name = sender()->objectName();
    if(name == "All"){
        if(this->boxen[0]->isChecked()){
            for(unsigned short i = 1; i < this->boxen.size(); ++i){
                this->boxen[i]->setChecked(1);
            }
        }
        else{
            for(unsigned short i = 1; i < this->boxen.size(); ++i){
                this->boxen[i]->setChecked(0);
            }
        }
    }

    //Toggle the 'All' check box depending on the state of the other check boxes
    for(unsigned short i = 1; i < this->boxen.size(); ++i){
        if(!(this->boxen[i]->isChecked())){
            this->boxen[0]->setChecked(0);
            break;
        }
        this->boxen[0]->setChecked(1);
    }
}

// Return a list of all current CFDP transactions
std::vector<std::string> Requests::listTransactions(){
  TRANSACTION t;
  std::vector<std::string> transactions;

  trans_list__open_walk();

  while (trans_list__get_next(&t)){
      transactions.push_back(cfdp_trans_as_string(t));
  }

  return transactions;
}
