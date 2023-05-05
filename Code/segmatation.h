#ifndef SEGMATATION_H
#define SEGMATATION_H
/************** Includes *************/
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
typedef struct
{
    float x, y, l, a, b;
} Point5D;

void point_lab(Point5D& pt);
void point_rgb(Point5D& pt);
void point_accum(Point5D& pt1, const Point5D& pt2);
void point_copy(Point5D& pt1, const Point5D& pt2);
float point_color_distance(const Point5D& pt1, const Point5D& pt2);
float point_spatial_distance(const Point5D& pt1, const Point5D& pt2);
void point_scale(Point5D& pt, float scale);
void point_set(Point5D& pt, float px, float py, float pl, float pa, float pb);
Mat mean_shift_segmentation( float spatial_bandwidth, float color_bandwidth);
double euclidean_distance(const Vec3b& a, const Vec3b& b);
Mat kmeans_segmentation_custom( int k, int max_iterations ) ;
Mat region_growing_segmentation(Mat& image, Point seed, float threshold, char color_flag);
Mat gray( Point seed, float threshold, char color_flag);
Mat colored( Point seed, float threshold, char color_flag);
double euclideanDistance(const vector<double> &p1, const vector<double> &p2);
double clustersDistance(const vector<vector<double>> &cluster1, const vector<vector<double>> &cluster2);
vector<vector<vector<double>>> initialClusters(Mat PixelsMatrix);
void mergeCluster(int clusters_num, Mat &pixels, vector<int> &labels, map<int, vector<double>> &centers,map<vector<double>, int> &cluster_map);
int predict_cluster(map<vector<double>, int>&cluster_map, vector<double> &point);
pair<Mat, Mat> imagePreperation(Mat&image);
Mat agglomerativeClustering(Mat &pixels, Mat &resized_image, int clusters_num);


#endif // SEGMATATION_H
