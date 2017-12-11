#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about/aboutui.h"
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include <QKeyEvent>
#include <QColorDialog>
#include <QKeySequence>
#include <QIcon>
#include <QDir>
#include <QStringList>
#include <QString>
#include <iostream>
#include <QLocale>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileInfo = QFileInfo();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    aboutui about_dialog;
    about_dialog.exec();
}

void MainWindow::on_actionopen_triggered()
{
    QString fileFullPath = QFileDialog::getOpenFileName(this, tr("Open Image"), "",
                                                        tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    this->fileInfo = QFileInfo(fileFullPath);
    
    if(!fileFullPath.isEmpty())
    {
        loadedImage = cv::imread(fileFullPath.toLocal8Bit().toStdString());
        if(loadedImage.empty())
        {
            qDebug("fail load image ");
        }
        displayMat(loadedImage);
        //clear undostack every loading a new image
        //add some statement;
        qDebug("test1");
        return;
    }
    qDebug("test2");
}


void MainWindow::displayMat(cv::Mat displayedImage)
{
    QImage transfromedImg;
    cv::Mat tempRgb;
    // Convert Mat BGR to QImage RGB
    if (displayedImage.channels() == 3)
    {
        cv::cvtColor(displayedImage, tempRgb, CV_BGR2RGB);
        transfromedImg = QImage((const unsigned char*)(tempRgb.data),
                                tempRgb.cols, tempRgb.rows,
                                tempRgb.cols * tempRgb.channels(),
                                QImage::Format_RGB888);
        qDebug("here is rgb format");
        qDebug("test3");
    }
    else
    {
        transfromedImg = QImage((const unsigned char*)(displayedImage.data),
                                displayedImage.cols, displayedImage.rows,
                                displayedImage.cols * displayedImage.channels(),
                                QImage::Format_Indexed8);
        qDebug("here is Index format");
    }
    scene = new QGraphicsScene(this);
    QPixmap showedPixImg = QPixmap::fromImage(transfromedImg);
    scene->addPixmap(showedPixImg);
    scene->setSceneRect(showedPixImg.rect());
    ui->ImageGraphicsView->setScene(scene);
}

void MainWindow::on_actionsave_triggered()
{
    if(savedImage.empty())
    {
        QMessageBox::information(this, "can't save null image", "there is no image to be saved! Please open a new file and process it");
    }
    else
    {
        cv::imwrite(fileInfo.filePath().toStdString(), savedImage);
    }

}

void MainWindow::updatwImage(cv::Mat img)
{
    savedImage = img;
    displayMat(img);
}
void MainWindow::on_actionexit_triggered()
{
    this->close();
}

void MainWindow::on_actionsave_as_triggered()
{
    if(savedImage.empty())
    {
        QMessageBox::information(this, "can't save null image", "there is no image to be saved! Please open a new file and process it");
    }
    else
    {
        QString imagePath = QFileDialog::getSaveFileName(this,
                                                         tr("Save File"),
                                                         "",
                                                         tr("Image File(*.png *.jpg *.jpeg *.bmp)"));
        if(!imagePath.isEmpty())
        {
            cv::imwrite(imagePath.toLocal8Bit().toStdString(), savedImage);
        }
    }
}

void MainWindow::on_actionCartoon_triggered()
{
    if(!loadedImage.empty())
    {

    }
    else
    {
        QMessageBox::information(this, "No Image", "there is no image to be processed");
    }
}
