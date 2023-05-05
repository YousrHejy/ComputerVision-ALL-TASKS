#ifndef FEATUREMATCHING_H
#define FEATUREMATCHING_H
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
extern double timetakenSSD, timetakenNCC;
/**************************************** functions ***************************************/
Mat image_featuring(string type,double thershold);
vector<DMatch> feature_matching_temp(Mat descriptor1, Mat descriptor2, string method,float threshold);
double calculateSSD(Mat desc_image1, Mat desc_image2);
double calculateNCC(Mat desc_image1, Mat desc_image2);
#endif // FEATUREMATCHING_H
