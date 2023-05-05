#ifndef HISTOGRAM_H
#define HISTOGRAM_H
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
Mat normalization_fun();
Mat automatic_global_threshold();
Mat manual_global_threshold(int threshold);
Mat local_threshold(int T_minus);
void Histogram(int histogram[]);
void CumulativeHist(int histogram[], int cumhistogram[]);
Mat DisplayHistogram(int histogram[]);
Mat equalization();
void showHistogram();
#endif // HISTOGRAM_H
