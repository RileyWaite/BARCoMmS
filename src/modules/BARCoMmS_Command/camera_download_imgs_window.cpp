#include "camera_download_imgs_window.h"
#include "ui_camera_download_imgs_window.h"

Camera_Download_Imgs_Window::Camera_Download_Imgs_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Camera_Download_Imgs_Window)
{
    ui->setupUi(this);

    //Set size of dialog window
    this->setFixedSize(408, 90);

    //Set the minimum and maximum values for the fields as defined in the data dicitonary
    ui->numImagesEdit->setMinimum(0);
    ui->numImagesEdit->setMaximum(10);      //what is actual maximum?

    //Call the closeEvent when the Ok or Cancel buttons are clicked
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

Camera_Download_Imgs_Window::~Camera_Download_Imgs_Window()
{
    delete ui;
}

//closeEvent, sends signal to Command with CAMERA_DOWNLOAD_IMGS command parameters
void Camera_Download_Imgs_Window::closeEvent(QCloseEvent *event)
{
    if(QDialog::result() == QDialog::Accepted)
    {
        //Capture user's input for command parameters
        numImages = ui->numImagesEdit->value();

        //Notify Command of user's input
        emit fields(numImages);

        //Close the dialog
        event->accept();
    }
    else
    {
        event->accept();
    }
}
