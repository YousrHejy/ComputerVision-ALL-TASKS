#ifndef ACTIVECONTOUR_H
#define ACTIVECONTOUR_H
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
/**************************************** Variable ***************************************/
// the candidate 8 movement
const int neighbors[9][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,0}, {0,1}, {1,-1}, {1,0}, {1,1}};
const int NUM_NEIGHBORS = 9;
/**************************************** functions ***************************************/
Mat activeContour( int radius , float alpha , int beta , int gamma);
double internalEnergy(const vector<Point>& snake , float alpha , int beta);
double totalEnergy(const Mat& grediant, const Mat& image, const vector<Point>& snake , float alpha , int beta ,int gamma);
double externalEnergy(const Mat& gradient, const Mat& image, const vector<Point>& snak , int gamma);
Mat basicImageGradient(const Mat& image);
bool isPointInsideImage(const Mat& image, const Point& point);
vector<Point> pointsOnCircle(Point center, int radius, int num_points);

#endif // ACTIVECONTOUR_H
