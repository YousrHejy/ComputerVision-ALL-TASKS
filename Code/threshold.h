#ifndef THRESHOLD_H
#define THRESHOLD_H
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

/************** functions *************/
Mat adaptiveOtsuThreshold(int blockSize);
Mat global_threshold_outsu ( int maxval) ;
Mat iterativeLocalThresholding( int blockSize, double epsilon);
Mat iterativeGlobalThresholding( double epsilon) ;
Mat spectral_threshold(Mat image);
Mat global();
#endif // THRESHOLD_H
