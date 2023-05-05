#include "featurematching.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <ctime> // include library
#include "mainwindow.h"
#include "filters.h"
using namespace std;
using namespace cv;
/**************************************** variables ***************************************/
Mat original_img, template_img;
vector<KeyPoint> kp1, kp2;
Mat descriptor1, descriptor2;
double timetakenSSD, timetakenNCC;
Mat dst3;
/**************************************** sum square difference ***************************************/
double calculateSSD(Mat desc_image1, Mat desc_image2) {
    double sum_square = 0.0;
    for (int m = 0; m < desc_image2.cols - 1; m++) {
        sum_square += pow(desc_image1.at<float>(m) - desc_image2.at<float>(m), 2);
    }
    double SSD = -sqrt(sum_square);
    return SSD;
}

/**************************************** NCC ***************************************/
double calculateNCC(Mat desc_image1, Mat desc_image2) {
    // Compute the mean and standard deviation of desc_image1
    Scalar mean1, stddev1;
    meanStdDev(desc_image1, mean1, stddev1);

    // Normalize desc_image1
    Mat norm_desc_image1 = (desc_image1 - mean1) / stddev1;

    // Compute the mean and standard deviation of desc_image2
    Scalar mean2, stddev2;
    meanStdDev(desc_image2, mean2, stddev2);

    // Normalize desc_image2
    Mat norm_desc_image2 = (desc_image2 - mean2) / stddev2;

    // Compute the element-wise product of the two normalized feature vectors
    Mat correlation_vector = norm_desc_image1.mul(norm_desc_image2);

    // Compute the mean of the correlation vector
    double ncc =mean(correlation_vector)[0];

    return ncc;
}

/**************************************** Matching features ***************************************/
vector<DMatch> feature_matching_temp(Mat descriptor1, Mat descriptor2, string method,float threshold) {
    int keyPoints1 = descriptor1.rows;
    int keyPoints2 = descriptor2.rows;

    // compute the time
    clock_t start;
    clock_t end;

    vector<DMatch> matched_features;
    double score;
    start = clock();


    for (int kp1 = 0; kp1 < keyPoints1; kp1++) {
        double distance = -numeric_limits<double>::infinity();
        int y_index = 2;
        for (int kp2 = 0; kp2 < keyPoints2; kp2++) {

            if (method == "SSD") {
                score = calculateSSD(descriptor1.row(kp1), descriptor2.row(kp2));

            }
            else{
                score = calculateNCC(descriptor1.row(kp1), descriptor2.row(kp2));
            }
            if (score > distance) {
                distance = score;
                y_index = kp2;
            }
        }
        DMatch feature(kp1, y_index, distance);

            if(feature.distance>threshold) {
                matched_features.push_back(feature);
        }
    }
    if(method=="SSD"){
        end = clock();
        timetakenSSD = (end - start) / (double)CLOCKS_PER_SEC;
        cout<<timetakenSSD<<endl;
    }else{
        end = clock();
        timetakenNCC = (end - start) / (double)CLOCKS_PER_SEC;
        cout<<timetakenNCC<<endl;
    }
    sort(matched_features.begin(), matched_features.end(), [](const DMatch& a, const DMatch& b) { return a.distance > b.distance; });

    return matched_features;
}

/**************************************** Pass images ***************************************/
Mat image_featuring(string type,double thershold){
    Convert_To_Gray(src,dst);
    Convert_To_Gray(src2,dst3);
    resize(dst, dst, Size(256, 256));
      resize(dst3, dst3, Size(256, 256));

      Ptr<SIFT> sift = SIFT::create();
      sift->detectAndCompute(dst, noArray(), kp1, descriptor1);
      sift->detectAndCompute(dst3, noArray(), kp2, descriptor2);

      vector<DMatch> matched_features = feature_matching_temp(descriptor1, descriptor2, type,thershold);
      vector<DMatch> matched;

      Mat matched_image;
      drawMatches(dst, kp1, dst3, kp2, matched_features, matched_image, Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
       return matched_image;
}
