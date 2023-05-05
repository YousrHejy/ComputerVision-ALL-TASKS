//
// Created by DELL on 3/7/2023.
//

#ifndef TEST_TESTING_H
#define TEST_TESTING_H


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>
using namespace std;
using namespace cv;

class testing {
private:
    Mat img; //Original Image
    Mat grayscaled; // Grayscale
    Mat gFiltered; // Gradient
    Mat sFiltered; //Sobel Filtered
    Mat angles; //Angle Map
    Mat non; // Non-maxima supp.
    Mat thres; //Double threshold and final
public:

    testing(); //Constructor
//    Mat Convert_To_Gray();
    vector<vector<double>> createFilter(int, int, double); //Creates a gaussian filter //Creates a gaussian filter
    Mat useFilter(Mat, vector<vector<double>>); //Use some filter
    Mat sobel(); //Sobel filtering
    Mat nonMaxSupp(); //Non-maxima supp.
    Mat threshold(Mat, int, int); //Double threshold and finalize picture
};


#endif //TEST_TESTING_H
//#endif //TEST_TESTING_H
