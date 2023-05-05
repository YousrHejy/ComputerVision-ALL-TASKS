#ifndef FILTERS_H
#define FILTERS_H
/**************************************** Includes ***************************************/
#include "mainwindow.h"
#define _USE_MATH_DEFINES
#include<cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/utility.hpp>
using namespace std;
using namespace cv;

/**************************************** functions ***************************************/
void Convert_To_Gray(const Mat &src, Mat &dst);
Mat gaussin_noise();
Mat uniform_noise();
Mat output_gaussin();
Mat output_uniform();
Mat spl();
Mat guasian_filter(int size);
Mat mean_filter(int size);
Mat median_filter(int size);
Mat filters( float  x[] ,  float  y[],int row , int col);
#endif // FILTERS_H
