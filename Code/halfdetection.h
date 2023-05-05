#ifndef HALFDETECTION_H
#define HALFDETECTION_H
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
Mat DrawHoughLines(vector<Vec2f> lines,Mat orginalImageWithHoughLines);
Mat houghLines( int minDist, double minAngle, int threshold);
Mat detectEllipses_circle(float threshold);
Mat detect_triangle();
#endif // HALFDETECTION_H
