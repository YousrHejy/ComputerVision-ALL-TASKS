#ifndef FREQUENCY_H
#define FREQUENCY_H
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
Mat return_image(int type,int radius);
Mat hyprid(int radius);
#endif // FREQUENCY_H
