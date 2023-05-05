#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"
#include "testing.h"
#include "segmatation.h"
#include <opencv2/opencv.hpp>
#include<QString>
#include <QFileDialog>
#include <QFile>
#include <string.h>
#include<QDir>
#include <QPixmap>
#include <QImage>
#include "filters.h"
#include "frequency.h"
#include "histogram.h"
#include "halfdetection.h"
#include "activecontour.h"
#include "harris.h"
#include "featurematching.h"
#include "sift.h"
#include "image.h"
#include "threshold.h"
float index1=0;
int index2=0;
float index3=0;
int index4=9;
int index5=255;
int index6=0;
int index7=0;
int index8=30;
int index9=9;
int index10=9;
Mat src;
Mat src2;

Mat dst;
Mat resized_up;
Mat imgg;
//Mat resized_up2;
String path1;
String path2;
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_3->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->circle_t->hide();
    ui->line_t->hide();
    ui->SSD->hide();
    ui->NCC->hide();
    ui->Kmean->hide();
    ui->kmean1->hide();
    ui->kmean2->hide();
    ui->mean_shift->hide();
     ui->itterative_local->hide();
     ui->otsu->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
}

void MainWindow::on_pushButton_7_clicked()
{

    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF)");
        String name =directory.toStdString();
        src=imread(name);
    int up_width = 512;
    int up_height = 512;
    resized_up=src;
    cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
    QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
    QPixmap pix=QPixmap::fromImage(image2);
    int width_img=ui->label->width();
    int height_img=ui->label->height();

    ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));

}
void MainWindow::on_pushButton_9_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF)");
        String name =directory.toStdString();
        src=imread(name);
        int up_width = 512;
        int up_height = 512;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();

        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}

void MainWindow::on_pushButton_10_clicked()
{
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }


}

void MainWindow::on_pushButton_12_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
}


void MainWindow::on_pushButton_13_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
}

void MainWindow::on_pushButton_20_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF)");
        String name =directory.toStdString();
        src=imread(name);
        int up_width = 512;
        int up_height = 512;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();
        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_pushButton_21_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF)");
        String name =directory.toStdString();
        src2=imread(name);
        int up_width = 512;
        int up_height = 512;
        resized_up=src2;
        cv::resize(src2,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label_2->width();
        int height_img=ui->label_2->height();

        ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_pushButton_22_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    ui->label_3->show();

    float index=ui->spinBox_6->value();
    index8=index;
    Mat Result=hyprid(index8);
    double minVal;
    double maxVal;
    Mat upper;
    double lower;
    Mat normalized_img;
    minMaxLoc( Result, &minVal, &maxVal );
    upper=Result-minVal;
    lower=maxVal-minVal;
    normalized_img=(upper/lower)*255;
    Mat modify;
    normalized_img.convertTo(modify,CV_8U);
    QImage qimage2(modify.data,modify.cols,modify.rows,QImage::Format_Grayscale8);
    QPixmap outputPix = QPixmap::fromImage(qimage2);
    int width_img2=ui->label_3->width();
    int height_img2=ui->label_3->height();
    ui->label_3->setPixmap(outputPix.scaled(width_img2,height_img2,Qt::KeepAspectRatio));

}


void MainWindow::on_pushButton_30_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    int histogram[256];
    Histogram( histogram);
    Mat Result=DisplayHistogram(histogram);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_3->width();
    int height_img2=ui->label_3->height();
    ui->label_3->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_pushButton_31_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    Mat Result= equalization();
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_pushButton_32_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    testing();


}

void MainWindow::on_high_textHighlighted(const QString &arg1)
{
    if(arg1=="sobel"){
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }
            float  x[] = { 1,0,-1,2,0,-2,1,0,-1 };
            float  y[] = { 1,2,1,0,0,0,-1,-2,-1};
            filters(x,y,3,3);
            Mat Result=filters(x,y,3,3);
            imwrite("Result.jpg", Result);
            QPixmap pix2("Result.jpg");
            int width_img2=ui->label_2->width();
            int height_img2=ui->label_2->height();
            ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));

    }else if(arg1=="berwit"){
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }
        float prewitt_x[]={-1, 0, 1, -1, 0, 1, -1, 0, 1};
        float prewitt_y[]={-1, -1, -1, 0, 0, 0, 1, 1, 1};
        Mat Result=filters(prewitt_x,prewitt_y,3,3);
        imwrite("Result.jpg", Result);
        QPixmap pix2("Result.jpg");
        int width_img2=ui->label_2->width();
        int height_img2=ui->label_2->height();
        ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));

    }else if(arg1=="robert"){
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }
        float roberts_x[]={0,1,-1,0};
        float roberts_y[]={1,0,0,-1};
        Mat Result=filters(roberts_x,roberts_y,2,2);
        imwrite("Result.jpg", Result);
        QPixmap pix2("Result.jpg");
        int width_img2=ui->label_2->width();
        int height_img2=ui->label_2->height();
        ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
    }
}


void MainWindow::on_noise_textHighlighted(const QString &arg1)
{
    if(arg1=="spi"){
        ui->add_g->hide();
        ui->add_u->hide();
        ui->add_s->show();
     }else if(arg1=="guasian"){
        ui->add_u->hide();
        ui->add_s->hide();
        ui->add_g->show();
    }else if(arg1=="uniform"){
        ui->add_s->hide();
        ui->add_g->hide();
        ui->add_u->show();
    }
}


void MainWindow::on_low_textHighlighted(const QString &arg1)
{
    if(arg1=="mean"){
        ui->median->hide();
        ui->guasian->hide();
        ui->mean->show();
     }else if(arg1=="guasian"){
        ui->median->hide();
        ui->guasian->show();
        ui->mean->hide();
    }else if(arg1=="median"){
        ui->median->show();
        ui->guasian->hide();
        ui->mean->hide();
    }
}


void MainWindow::on_add_g_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->add_g->value();
    index1=index;
    Mat Result=output_gaussin();
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_add_u_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->add_u->value();
    index3=index;
    Mat Result=output_uniform();
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_add_s_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    int index=ui->add_s->value();
    index2=index;
    Mat Result=spl();
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_guasian_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->guasian->value();
    index4=index*index;
    Mat Result=guasian_filter(index4);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_mean_editingFinished()
{
    float index=ui->mean->value();
    index9=index*index;
    Mat Result=mean_filter(index9);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_median_editingFinished()
{
    float index=ui->median->value();
    index10=index*index;
    Mat Result=median_filter(index10);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}

void MainWindow::on_options_textHighlighted(const QString &arg1)
{
    if(arg1=="normalize"){
        ui->local->hide();
        ui->manual->hide();
        ui->normalize->show();
     }else if(arg1=="manual"){
        ui->local->hide();
        ui->manual->show();
        ui->normalize->hide();
    }else if(arg1=="local"){
        ui->local->show();
        ui->manual->hide();
        ui->normalize->hide();
    }else if(arg1=="auto"){
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }
        Mat Result=automatic_global_threshold();
        imwrite("Result.jpg", Result);
        QPixmap pix2("Result.jpg");
        int width_img2=ui->label_2->width();
        int height_img2=ui->label_2->height();
        ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
        }
}


void MainWindow::on_normalize_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->normalize->value();
    index5=index;
    Mat Result=normalization_fun();
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_manual_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->manual->value();
    index6=index;
    Mat Result=manual_global_threshold(index6);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));

}


void MainWindow::on_local_editingFinished()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->local->value();
    index7=index;
    Mat Result=local_threshold(index7);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}




void MainWindow::on_Histogram_textHighlighted(const QString &arg1)
{
    if(arg1=="Gray"){
             ui->label_3->show();
        if ( !src.data )
            {
                printf("No image data \n");
                return;
            }
        int histogram[256];
        Histogram( histogram);
        imgg=DisplayHistogram(histogram);
            int up_width = 300;
            int up_height = 300;
        //    Convert_To_Gray(src,dst);
            resized_up=imgg;
            cv::resize(imgg,resized_up, Size(up_width, up_height), INTER_LINEAR);
            QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_Grayscale8);
            QPixmap pix=QPixmap::fromImage(image2);
            int width_img=ui->label_3->width();
            int height_img=ui->label_3->height();
            ui->label_3->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
    }else if(arg1=="Colored"){
        ui->label_3->show();
        ui->label_5->show();
        ui->label_4->show();
        showHistogram();
        QPixmap pix("green.jpg");
        QPixmap pix1("red.jpg");
        QPixmap pix2("blue.jpg");
        int width_img=ui->label_5->width();
        int height_img=ui->label_5->height();
        ui->label_5->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
        int width_img1=ui->label_3->width();
        int height_img1=ui->label_3->height();
        ui->label_3->setPixmap(pix1.scaled(width_img1,height_img1,Qt::KeepAspectRatio));
        int width_img2=ui->label_4->width();
        int height_img2=ui->label_4->height();
        ui->label_4->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
    }
}




//void MainWindow::on_circle_t_sliderReleased()
//{

//if ( !src.data )
//    {
//        printf("No image data \n");
//        return;
//    }
//float index=ui->circle_t->value();
//index=index/100;
//Mat Result= detectEllipses_circle(0.01);
//imwrite("Result.jpg", Result);
//QPixmap pix2("Result.jpg");
//int width_img2=ui->label_2->width();
//int height_img2=ui->label_2->height();
//ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
//}


//void MainWindow::on_line_t_sliderReleased()
//{
//    if ( !src.data )
//        {
//            printf("No image data \n");
//            return;
//        }
//    float index=ui->line_t->value();
//    int r = 1;
//    double theta = CV_PI/180;
//    vector<Vec2f> lines;
//    Mat Result;
//    // Apply HoughLines transformation
//   Result = houghLines( r, theta, index);
//   imwrite("Result.jpg", Result);
//   QPixmap pix2("Result.jpg");
//   int width_img2=ui->label_2->width();
//   int height_img2=ui->label_2->height();
//   ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
//}


void MainWindow::on_detection_textHighlighted(const QString &arg1)
{
    if(arg1=="Line"){
     ui->line_t->show();
     ui->circle_t->hide();
    }else if(arg1=="Triangle"){
        ui->circle_t->hide();
        ui->line_t->hide();
        Mat Result= detect_triangle();
        imwrite("Result.jpg", Result);
        QPixmap pix2("Result.jpg");
        int width_img2=ui->label_2->width();
        int height_img2=ui->label_2->height();
        ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
    }else if(arg1=="Circle"){
        ui->circle_t->show();
        ui->line_t->hide();

    }
}


void MainWindow::on_Upload_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
        String name =directory.toStdString();
        src=imread(name);
        int up_width = 512;
        int up_height = 512;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();

        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}



void MainWindow::on_Upload_contour_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
        String name =directory.toStdString();
        src=imread(name);
        int up_width = 512;
        int up_height = 512;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();

        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_contour_clicked()
{
    int alpha= ui->Alpha->value();
    int beta=ui->Beta->value();
    int gama=ui->Gama->value();
    int radius=ui->Radius->value();
    Mat Result=activeContour( radius ,  alpha , beta ,  gama);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_circle_t_editingFinished()
{

    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->circle_t->value();
    Mat Result= detectEllipses_circle(index);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_line_t_editingFinished()
{

    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    float index=ui->line_t->value();
    int r = 1;
    double theta = CV_PI/180;
    vector<Vec2f> lines;
    Mat Result;
    // Apply HoughLines transformation
   Result = houghLines( r, theta, index);
   imwrite("Result.jpg", Result);
   QPixmap pix2("Result.jpg");
   int width_img2=ui->label_2->width();
   int height_img2=ui->label_2->height();
   ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_upload_harris_clicked()
{

    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
        String name =directory.toStdString();
        src=imread(name);
        int up_width = 300;
        int up_height = 300;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();

        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_Harris_clicked()
{
    if ( !src.data )
        {
            printf("No image data \n");
            return;
        }
    Mat Result;
    double k = 0.04;
    int window_size = 4;
    double threshold = 100000.00;
    Result=find_harris_corners( k, window_size, threshold);
    imwrite("Result.jpg", Result);
    QPixmap pix2("Result.jpg");
    int width_img2=ui->label_2->width();
    int height_img2=ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_upload_img_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
        String name =directory.toStdString();
        path1=name;
        src=imread(name);
        int up_width = 300;
        int up_height = 300;
        resized_up=src;
        cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label->width();
        int height_img=ui->label->height();

        ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_upload_temp_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                  tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
        String name =directory.toStdString();
       path2=name;
        src2=imread(name);
        int up_width = 300;
        int up_height = 300;
        resized_up=src2;
        cv::resize(src2,resized_up, Size(up_width, up_height), INTER_LINEAR);
        QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
        QPixmap pix=QPixmap::fromImage(image2);
        int width_img=ui->label_2->width();
        int height_img=ui->label_2->height();

        ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_match_textHighlighted(const QString &arg1)
{
    if(arg1=="SSD"){
     ui->SSD->show();
     ui->NCC->hide();
    }else if(arg1=="NCC"){
        ui->SSD->hide();
        ui->NCC->show();

    }
}


void MainWindow::on_NCC_editingFinished()
{
    if ( !src.data||!src2.data )
        {
            printf("No image data \n");
            return;
        }
ui->label_3->show();
Mat Result= image_featuring("NCC",ui->NCC->value());
int up_width = 400;
int up_height = 400;
resized_up=Result;
cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
QPixmap pix=QPixmap::fromImage(image2);
int width_img2=ui->label_3->width();
int height_img2=ui->label_3->height();
ui->label_3->setPixmap(pix.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_SSD_editingFinished()
{
    if ( !src.data ||!src2.data )
        {
            printf("No image data \n");
            return;
        }
    QString t = QString().asprintf("%0.2f", timetakenSSD);
    ui->label_3->show();
    int value=ui->SSD->value();
    Mat Result= image_featuring("SSD",-value);
    int up_width = 400;
    int up_height = 400;
    resized_up=Result;
    cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
    QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
    QPixmap pix=QPixmap::fromImage(image2);
   /* imwrite("Result.jpg", image2);
    QP*//*ixmap pix2("Result.jpg");*/

    int width_img2=ui->label_3->width();
    int height_img2=ui->label_3->height();
    ui->label_3->setPixmap(pix.scaled(width_img2,height_img2,Qt::KeepAspectRatio));
}


void MainWindow::on_sift_clicked()
{
 ui->label_3->show();
  cout<<path1<<endl;
    Image img(path1);
    Image img2(path2);
    img = rgb_to_grayscale(img);
    img2 = rgb_to_grayscale(img2);
    std::vector<sift::Keypoint> kps1 = sift::find_keypoints_and_descriptors(img);
    std::vector<sift::Keypoint> kps2 = sift::find_keypoints_and_descriptors(img2);
    std::vector<std::pair<int, int>> matches = sift::find_keypoint_matches(kps1, kps2);
      Image feature_matches = sift::draw_matches(img, img2, kps1, kps2, matches);
       feature_matches.save("E:/SBME/3rd/Second Term/CV/images/engineering.jpeg");
       Mat Result = imread("E:/SBME/3rd/Second Term/CV/images/engineering.jpeg");
       int up_width = 400;
       int up_height = 400;
       resized_up=Result;
       cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
       QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
       QPixmap pix=QPixmap::fromImage(image2);
       int width_img2=ui->label_3->width();
       int height_img2=ui->label_3->height();
       ui->label_3->setPixmap(pix.scaled(width_img2,height_img2,Qt::KeepAspectRatio));

}


void MainWindow::on_Segm_textHighlighted(const QString &arg1)
{
    if(arg1=="Kmean"){
        ui->Kmean->show();
        ui->kmean1->hide();
        ui->kmean2->hide();
        ui->mean_shift->hide();
        ui->x1->hide();
        ui->y1->hide();
        ui->reigon_threshold->hide();

       }else if(arg1=="agglomerative"){
           ui->Kmean->hide();
           ui->kmean1->hide();
           ui->kmean2->hide();
           ui->mean_shift->hide();
           ui->x1->hide();
           ui->y1->hide();
           ui->reigon_threshold->hide();

       }else if(arg1=="mean shift"){
        ui->Kmean->hide();
        ui->kmean1->show();
        ui->kmean2->show();
        ui->mean_shift->show();
        ui->x1->hide();
        ui->y1->hide();
        ui->reigon_threshold->hide();
    }else if(arg1=="region grow"){
        ui->Kmean->hide();
        ui->kmean1->hide();
        ui->kmean2->hide();
        ui->mean_shift->hide();
        ui->x1->show();
        ui->y1->show();
        ui->reigon_threshold->show();
    }else if(arg1=="region colored"){
        ui->Kmean->hide();
        ui->kmean1->hide();
        ui->kmean2->hide();
        ui->mean_shift->hide();
        ui->x1->show();
        ui->y1->show();
        ui->reigon_threshold->show();

    }
}


void MainWindow::on_upload_seg_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                     tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
           String name =directory.toStdString();
           src=imread(name);
           int up_width = 300;
           int up_height = 300;
           resized_up=src;
           cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
           QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
           QPixmap pix=QPixmap::fromImage(image2);
           int width_img=ui->label->width();
           int height_img=ui->label->height();

           ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_Kmean_editingFinished()
{
    if ( !src.data )
           {
               printf("No image data \n");
               return;
           }
       ui->label_2->show();
       Mat Result= kmeans_segmentation_custom( ui->Kmean->value(),10 );
       imwrite("Result.jpg", Result);
       int up_width = 300;
       int up_height = 300;
       resized_up=Result;
       cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
       QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
       QPixmap pix=QPixmap::fromImage(image2);
       int width_img=ui->label->width();
       int height_img=ui->label->height();

       ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_upload_threshold_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                     tr("Find Files"), QDir::homePath(),"Image files (*.jpg *.png *.JFIF *.jpeg)");
           String name =directory.toStdString();
           src=imread(name);
           int up_width = 300;
           int up_height = 300;
           resized_up=src;
           cv::resize(src,resized_up, Size(up_width, up_height), INTER_LINEAR);
           QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
           QPixmap pix=QPixmap::fromImage(image2);
           int width_img=ui->label->width();
           int height_img=ui->label->height();

           ui->label->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}




void MainWindow::on_threshold_textHighlighted(const QString &arg1)
{
    if(arg1=="global otsu"){
        ui->otsu->hide();
         ui->itterative_local->hide();
        if ( !src.data )
               {
                   printf("No image data \n");
                   return;
               }
           ui->label_2->show();
           Mat Result= global_threshold_outsu ( 255);
           imwrite("Result.jpg", Result);
           int up_width = 300;
           int up_height = 300;
           resized_up=Result;
           cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
           QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
           QPixmap pix=QPixmap::fromImage(image2);
           int width_img=ui->label->width();
           int height_img=ui->label->height();

           ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));

       }else if(arg1=="local otsu"){
     ui->itterative_local->hide();
     ui->otsu->show();

       }else if(arg1=="global Itterative"){
        ui->itterative_local->hide();
        ui->otsu->hide();
        if ( !src.data )
               {
                   printf("No image data \n");
                   return;
               }
           ui->label_2->show();
           Mat Result= iterativeGlobalThresholding( 0.1) ;
           imwrite("Result.jpg", Result);
           int up_width = 300;
           int up_height = 300;
           resized_up=Result;
           cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
           QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
           QPixmap pix=QPixmap::fromImage(image2);
           int width_img=ui->label->width();
           int height_img=ui->label->height();

           ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
    }else if(arg1=="local Itterative"){
      ui->itterative_local->show();
      ui->otsu->hide();
    }else if(arg1=="spectral"){
        ui->itterative_local->hide();
        ui->otsu->hide();
        if ( !src.data )
               {
                   printf("No image data \n");
                   return;
               }
           ui->label_2->show();
           Mat Result=  global() ;
           cout<<Result<<endl;
           imwrite("Result.jpg", Result);
           int up_width = 512;
           int up_height = 512;
           resized_up=Result;
           cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
           QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_Grayscale16);
           QPixmap pix=QPixmap::fromImage(image2);
           int width_img=ui->label->width();
           int height_img=ui->label->height();

           ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
    }
}


void MainWindow::on_mean_shift_clicked()
{
    if ( !src.data )
           {
               printf("No image data \n");
               return;
           }
       ui->label_2->show();
       Mat Result=  mean_shift_segmentation( ui->kmean1->value(), ui->kmean2->value());
       imwrite("Result.jpg", Result);
       int up_width = 300;
       int up_height = 300;
       resized_up=Result;
       cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
       QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
       QPixmap pix=QPixmap::fromImage(image2);
       int width_img=ui->label->width();
       int height_img=ui->label->height();

       ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_itterative_local_editingFinished()
{
    if ( !src.data )
           {
               printf("No image data \n");
               return;
           }
       ui->label_2->show();
       Mat Result=  iterativeLocalThresholding(ui->itterative_local->value(),0.1 );
       imwrite("Result.jpg", Result);
       int up_width = 300;
       int up_height = 300;
       resized_up=Result;
       cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
       QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
       QPixmap pix=QPixmap::fromImage(image2);
       int width_img=ui->label->width();
       int height_img=ui->label->height();

       ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_otsu_editingFinished()
{
    if ( !src.data )
           {
               printf("No image data \n");
               return;
           }
       ui->label_2->show();
       Mat Result=  adaptiveOtsuThreshold(ui->otsu->value()) ;
       imwrite("Result.jpg", Result);
       int up_width = 300;
       int up_height = 300;
       resized_up=Result;
       cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
       QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
       QPixmap pix=QPixmap::fromImage(image2);
       int width_img=ui->label->width();
       int height_img=ui->label->height();

       ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_gray_clicked()
{
    Point seed(ui->x1->value(), ui->y1->value());

   if ( !src.data )
          {
              printf("No image data \n");
              return;
          }
      ui->label_2->show();
      Mat Result=  gray(  seed, ui->reigon_threshold->value(), 0);
      imwrite("Result.jpg", Result);
      int up_width = 300;
      int up_height = 300;
      resized_up=Result;
      cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
      QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
      QPixmap pix=QPixmap::fromImage(image2);
      int width_img=ui->label->width();
      int height_img=ui->label->height();

      ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));
}


void MainWindow::on_coloredReigion_clicked()
{
    Point seed(ui->x1->value(), ui->y1->value());

   if ( !src.data )
          {
              printf("No image data \n");
              return;
          }
      ui->label_2->show();
      Mat Result=      colored(  seed,ui->reigon_threshold->value(),1);
      imwrite("Result.jpg", Result);
      int up_width = 300;
      int up_height = 300;
      resized_up=Result;
      cv::resize(Result,resized_up, Size(up_width, up_height), INTER_LINEAR);
      QImage image2((uchar*)resized_up.data,resized_up.cols,resized_up.rows,QImage::Format_BGR888);
      QPixmap pix=QPixmap::fromImage(image2);
      int width_img=ui->label->width();
      int height_img=ui->label->height();

      ui->label_2->setPixmap(pix.scaled(width_img,height_img,Qt::KeepAspectRatio));

}

