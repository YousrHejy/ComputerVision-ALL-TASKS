#ifndef HARRIS_H
#define HARRIS_H
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
Mat find_harris_corners(double k, int window_size, double threshold);

#endif // HARRIS_H
