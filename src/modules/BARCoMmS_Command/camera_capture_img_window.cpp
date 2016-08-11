#include "camera_capture_img_window.h"
#include "ui_camera_capture_img_window.h"

Camera_Capture_Img_Window::Camera_Capture_Img_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Camera_Capture_Img_Window)
{
    ui->setupUi(this);

    //Set size of dialog window
    this->setFixedSize(323, 110);

    //Set the minimum and maximum values for the fields as defined in the data dicitonary
    avgBrightnessEdit->setMinimum(0);
    avgBrightnessEdit->setMaximum(255);
    fillEdit->setMinimum(0);
    fillEdit->setMaximum(255);

    //Call the closeEvent when the Ok or Cancel buttons are clicked
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(close()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}

Camera_Capture_Img_Window::~Camera_Capture_Img_Window()
{
    delete ui;
}

//closeEvent, sends signal to Command with CAMERA_CAPTURE_IMG command parameters
void Camera_Capture_Img_Window::closeEvent(QCloseEvent *event)
{
    if(QDialog::result() == QDialog::Accepted)
    {
        //Capture user's input for command parameters
        avgBrightness = avgBrightnessEdit->value();
        fill = fillEdit->value();

        //Notify Command of user's input
        emit fields(avgBrightness, fill);

        //Close the dialog
        event->accept();
    }
    else
    {
        event->accept();
    }
}
