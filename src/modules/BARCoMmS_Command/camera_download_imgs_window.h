#ifndef CAMERA_DOWNLOAD_IMGS_WINDOW_H
#define CAMERA_DOWNLOAD_IMGS_WINDOW_H

#include <QDialog>
#include <QObject>
#include <QCloseEvent>
#include <QSpinBox>
#include <QDebug>

namespace Ui {
class Camera_Download_Imgs_Window;
}

class Camera_Download_Imgs_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Camera_Download_Imgs_Window(QWidget *parent = 0);
    ~Camera_Download_Imgs_Window();

    //closeEvent, sends signal to Command with CAMERA_DOWNLOAD_IMGS command parameters
    void closeEvent(QCloseEvent *);

    //Spinbox for user to choose the number of images to send, value is stored as int and sent as command parameter
    QSpinBox *numImagesEdit;
    int numImages;

signals:

    //Signal to Command with CAMERA_DOWNLOAD_IMGS command parameter
    void fields(int);

private:
    Ui::Camera_Download_Imgs_Window *ui;
};

#endif // CAMERA_DOWNLOAD_IMGS_WINDOW_H
