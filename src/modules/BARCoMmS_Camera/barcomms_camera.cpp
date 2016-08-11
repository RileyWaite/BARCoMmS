#include "barcomms_camera.h"
#include "ui_barcomms_camera.h"
#include "qstring.h"
#include "qfiledialog.h"
#include "qopengltexture.h"
#include "qopenglfunctions.h"
#include "qdatetime.h"
#include "qdebug.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>

BARCoMmS_Camera::BARCoMmS_Camera(QWidget* parent) : QMainWindow(parent), ui(new Ui::BARCoMmS_Camera)
{
    ui->setupUi(this);

    QSurfaceFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile( QSurfaceFormat::CoreProfile );
    QSurfaceFormat::setDefaultFormat(glFormat);
    ui->mainImage->setFormat(glFormat);

    QString mPath = "/";

    watcher = new QFileSystemWatcher();

    watcher->addPath(mPath);

    initializeImageList(mPath);

    initializeBrightnessSlider();

    QObject::connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(displayNewestImage(QString)));
    QObject::connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(generateImageList(QString)));
    QObject::connect(ui->mainImage, SIGNAL(GLStartup()), this, SLOT(displayFirstImage()));
    QObject::connect(ui->mainImage, SIGNAL(imageChanged(QString)), this, SLOT(changeTimeStamp(QString)));
}

BARCoMmS_Camera::~BARCoMmS_Camera()
{
    delete ui;
}

void BARCoMmS_Camera::on_openImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));       //Opens a file dialogue which lets the user select a file to open.

    if(imagePath.isNull() == false)
    {
        imageObject = new QImage();
        imageObject->load(imagePath);

        iPath = &imagePath;

         ui->mainImage->loadTextureImg(imagePath);
        //ui->mainImage->mercator(imagePath);
    }
}

void BARCoMmS_Camera::displayNewestImage(const QString &path)
{
    //qDebug() << "Display newest image called.";
    QDir dir(path);

    QStringList filters;
    filters << "*.png" << "*.jpg";

    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Time);

    QFileInfo newest;

    foreach(QFileInfo fileInfo, list)
    {
        if(newest.filePath().isEmpty() || fileInfo.created() > newest.created())
        {
            newest = fileInfo;
        }
    }

    //qDebug() << "Newest file is: " << newest.filePath();

    ui->mainImage->loadTextureImg(newest.filePath());
    imageListSize++;
}

void BARCoMmS_Camera::on_redSlider_valueChanged(int value)
{
    ui->mainImage->changeValue(value, "rTint");

    ui->mainImage->update();
}

void BARCoMmS_Camera::on_greenSlider_valueChanged(int value)
{
    ui->mainImage->changeValue(value, "gTint");

    ui->mainImage->update();
}

void BARCoMmS_Camera::on_blueSlider_valueChanged(int value)
{
    ui->mainImage->changeValue(value, "bTint");

    ui->mainImage->update();
}

void BARCoMmS_Camera::on_pictureSlider_valueChanged(int value)
{
    //qDebug() << value;

    ui->mainImage->loadTextureImg(imageList.at(value));
}

void BARCoMmS_Camera::initializeImageList(const QString &path)
{
    //qDebug() << "InitializeImageList called.";
    QStringList filters;
    filters << "*.png" << "*.jpg";

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Time);

    QFileInfo temp;
    int flag = 0;

    //qDebug() << list.size();

    imageListSize = list.size();

    if(imageListSize != 0)
    {
        // Sorts images in order from newest to oldest
        for(int i = 0; i < list.size() && flag; i++)
        {
            flag = 0;
            for(int j = 0; j < list.size() - 1; j++)
            {
                if(list.at(j+1).created() > list.at(j).created())
                {
                    temp = list.at(j);
                    list[j] = list[j+1];
                    list[j+1] = list[j];

                    flag = 1;
                }
            }
        }


        imageList.resize(list.size());

        for(int k = 0; k < list.size(); k++)
        {
            imageList[k].append(list[k].filePath());
        }

        ui->pictureSlider->setMaximum(imageList.size() - 1);
    }
    else
    {
        ui->pictureSlider->setMaximum(0);
    }
}

void BARCoMmS_Camera::generateImageList(const QString &path)
{
    qDebug() << "Generate Image LIst called.";
    QStringList filters;
    filters << "*.png" << "*.jpg";

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Time);

    QFileInfo temp;

    //qDebug() << list.size() << "\n" << imageListSize;

    if(list.size() >= imageListSize)
    {
        QFileInfo newest;

        foreach(QFileInfo fileInfo, list)
        {
            if(fileInfo.created() > newest.created())
            {
                newest = fileInfo;
            }
        }

        imageList.prepend(newest.filePath());

        ui->pictureSlider->setMaximum(imageList.size() - 1);
        ui->pictureSlider->setValue(0);

        imageListSize++;
    }
    else
    {
        imageList.remove(0);
        ui->pictureSlider->setMaximum(imageList.size()-1);

        imageListSize--;
    }
}

void BARCoMmS_Camera::displayFirstImage()
{
    ui->numberOfImagesInDirectory->setText("Number of Images in Current Directory: " + QString::number(imageList.size()));

    qDebug() << imageList.size();

    if(imageList.size() != 0)
    {
        ui->mainImage->loadTextureImg(imageList[0]);
    }
    else
    {
        ui->mainImage->loadTextureImg(":/noImageAvailable.jpg");
    }
}

void BARCoMmS_Camera::on_contrastSlider_valueChanged(int value)
{
    ui->mainImage->changeValue(value, "contrast");

    ui->mainImage->update();
}

void BARCoMmS_Camera::on_brightnessSlider_valueChanged(int value)
{
    ui->mainImage->changeValue(value, "brightness");

    ui->mainImage->update();
}

void BARCoMmS_Camera::initializeBrightnessSlider()
{
    ui->brightnessSlider->setRange(-50,50);

    ui->brightnessSlider->setValue(0);
}

void BARCoMmS_Camera::on_brightnessSlider_sliderReleased()
{
    if(ui->brightnessSlider->value() >= -10 && ui->brightnessSlider->value() <= 10)
    {
        ui->brightnessSlider->setValue(0);
    }
}

void BARCoMmS_Camera::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit\nBARCoMmS Camera?",
                                                              QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        event->accept();
    }
    else{
        event->ignore();
    }
}

void BARCoMmS_Camera::changeTimeStamp(QString imagePath)
{
    //qDebug() << "Change time stamp called.";
    QFileInfo info(imagePath);

    ui->timeStamp->setText("Created: " + info.created().toString() + "\t\tFile Path: " + imagePath);
}

void BARCoMmS_Camera::changeNumberOfImagesInDirectory(int num)
{
    qDebug() << num;
    ui->numberOfImagesInDirectory->setText("Number of Images in Current Directory: " + QString::number(num));
}

void BARCoMmS_Camera::on_changeDirectory_clicked()
{
    bool ok;

    //QString newPath = QInputDialog::getText(this, tr("Change the Image Directory"),tr("New Path:"), QLineEdit::Normal,QDir::home().dirName(), &ok);

    QString newPath = QFileDialog::getExistingDirectory(this, tr("Select a Folder"), tr("New Path"), QFileDialog::ShowDirsOnly);

    if(!newPath.isEmpty())
    {
        //qDebug() << watcher->directories().at(0);
        watcher->removePath(watcher->directories().at(0));
        watcher->addPath(newPath);

        imageList.clear();
        imageList.squeeze();

        QStringList filters;
        filters << "*.png" << "*.jpg";

        QDir dir(newPath);
        QFileInfoList list = dir.entryInfoList(filters,QDir::Files,QDir::Time);

        changeNumberOfImagesInDirectory(list.size());

        if(list.size() != 0)
        {
            initializeImageList(newPath);
            displayNewestImage(newPath);
        }
        else
        {
            initializeImageList(newPath);
            ui->mainImage->loadTextureImg(":/noImageAvailable.jpg");
        }
    }
}
