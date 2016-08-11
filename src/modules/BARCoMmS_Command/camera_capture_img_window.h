#ifndef CAMERA_CAPTURE_IMG_WINDOW_H
#define CAMERA_CAPTURE_IMG_WINDOW_H

#include <QDialog>
#include <QObject>
#include <QSlider>
#include <QCloseEvent>
#include <QDebug>
#include <QDialogButtonBox>

namespace Ui {
class Camera_Capture_Img_Window;
}

class Camera_Capture_Img_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Camera_Capture_Img_Window(QWidget *parent = 0);
    ~Camera_Capture_Img_Window();

    //closeEvent, sends signal to Command with CAMERA_CAPTURE_IMG command parameters
    void closeEvent(QCloseEvent *);

    //Sliders for user to choose the exposure and fill of the images, values are stored as ints and sent as command parameters
    QSlider *avgBrightnessEdit = new QSlider();
    QSlider *fillEdit = new QSlider();
    int avgBrightness, fill;

signals:

    //Signal to Command with CAMERA_CAPTURE_IMG command parameters
    void fields(int, int);

private:
    Ui::Camera_Capture_Img_Window *ui;
};

#endif // CAMERA_CAPTURE_IMG_WINDOW_H
