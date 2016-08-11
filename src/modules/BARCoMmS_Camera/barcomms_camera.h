#ifndef BARCOMMS_CAMERA_H
#define BARCOMMS_CAMERA_H

#include <QMainWindow>
#include <QString>
#include "qgraphicsscene.h"
#include "qopengl.h"
#include "qfilesystemwatcher.h"
#include <QTime>
#include <vector>

namespace Ui {
class BARCoMmS_Camera;
}

class BARCoMmS_Camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit BARCoMmS_Camera(QWidget *parent = 0);
    ~BARCoMmS_Camera();

    void closeEvent(QCloseEvent *event);

    /* Initializes the list of QStrings that
     * contain the paths to the images in the
     * specified path
     */
    void initializeImageList(const QString &path);

private slots:
    /* Gets called when the "openImage" button is
     * clicked...
     *
     * It opens the file Directory and allows the
     * user to select a .png or .jpeg file they
     * want to display on the OpenGL Widget.
     *
     * It then passes the imagePath to QGLWidget's
     * displayImage function.
     */
    void on_openImage_clicked();
    /* Displays the newest image in the specified
     * path by comparing each file's .created()
     * values and finding the newest one.
     *
     * Displays via QGLWidget's displayImage
     */
    void displayNewestImage(const QString &path);
    /* Changes the red tint value of the image based
     * on the redSlider value.
     *
     * Makes it look all evil... >:)
     */
    void on_redSlider_valueChanged(int value);
    /* Changes the green tint value of the image based
     * on the greenSlider value.
     */
    void on_greenSlider_valueChanged(int value);
    /* Changes the blue tint value of the image based
     * on the blueSlider value.
     */
    void on_blueSlider_valueChanged(int value);
    /* Changes the picture displayed based on the
     * pictureSlider value.
     *
     * It does this using the vector of images,
     * imageList
     */
    void on_pictureSlider_valueChanged(int value);
    /* Generates a new imageList each time the
     * the specified directory is modified.
     *
     * If new file: Adds one to the imagelist size
     * and displays the new image.
     *
     * If delete file: Subtracts one from the
     * imageList size and deletes that QString from
     * the list.
     */
    void generateImageList(const QString &path);
    /* Displays the newest image in the directory.
     *
     * Called on startup in resizeGL()
     */
    void displayFirstImage();
    /* Changes the contrast value of the image based
     * on the contrastSlider value.
     */
    void on_contrastSlider_valueChanged(int value);
    /* Changes the brightness value of the image based
     * on the brightnessSlider value.
     */
    void on_brightnessSlider_valueChanged(int value);
    /* Initializes the brightness slider to 0 and sets
     * the minimum and maximum to -50 and 50, respectively.
     */
    void initializeBrightnessSlider();
    /* Sets a margin of error for returning the
     * brightness to 0. If the user releases the slider
     * within 15 ticks of 0, it sets the slider value
     * to 0.
     */
    void on_brightnessSlider_sliderReleased();

    void changeTimeStamp(QString imagePath);

    void on_changeDirectory_clicked();

    void changeNumberOfImagesInDirectory(int num);

public:
    Ui::BARCoMmS_Camera *ui;
    QPixmap image;
    QImage *imageObject;
    GLuint *tex;
    QString *iPath;
    QFileSystemWatcher *watcher;
    QTime *pastTime;
    QVector<QString> imageList;
    int imageListSize;
};

#endif // BARCOMMS_CAMERA_H
