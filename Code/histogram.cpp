
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include <QFileDialog>
#include <QFile>
#include <string.h>
#include<QDir>
#include <QPixmap>
#include <QImage>
#include "histogram.h"
#include "filters.h"
double minVal;
double maxVal;
Mat upper;
double lower;
Mat normalized_img;
/********************************************** Normalization *****************************************************/
Mat normalization_fun(){
    Convert_To_Gray(src,dst);
    minMaxLoc( dst, &minVal, &maxVal );
    upper=dst-minVal;
    lower=maxVal-minVal;
    normalized_img=(upper/lower)*index5;
    waitKey();

    return normalized_img;

}
/********************************************** Thresholding *****************************************************/

// Function to differentiate between the image objects and the background using global thresholding
Mat automatic_global_threshold() {
    // Initialisations
    Convert_To_Gray(src,dst);
    Mat image=dst.clone();
    int pixels_avg = 0;
    int pixels_sum = 0;

    // Get the dimensions of the image
    int rows = image.rows;
    int cols = image.cols;

    // Iterate on the pixels of the image
    for (int i=0 ; i<rows ; i++)
    {
        for (int j=0 ; j<cols ; j++)
        {
            // Calculate the summation of the pixels
            pixels_sum = pixels_sum + image.at<uchar>(i,j);
        }
    }

    // Calculate the average of the pixels
    pixels_avg = pixels_sum / (rows * cols);

    // Set the threshold to be the average of the pixels
    int threshold = pixels_avg;

    for (int i=0 ; i<rows ; i++)
    {
        for (int j=0 ; j<cols ; j++)
        {
            // check the pixel value
            if ( image.at<uchar>(i,j) < threshold )
            {
                image.at<uchar>(i,j) = 0;
            }

            else
            {
                image.at<uchar>(i,j) = 255;
            }

        }
    }
    waitKey();
    return image;
}

// Function to differentiate between the image objects and the background using global thresholding
Mat manual_global_threshold(int threshold) {
    // Get the dimensions of the image
    Convert_To_Gray(src,dst);
    Mat image=dst.clone();
    int rows = image.rows;
    int cols = image.cols;

    // Iterate on the pixels of the image
    for (int i=0 ; i<rows ; i++)
    {
        for (int j=0 ; j<cols ; j++)
        {
            // check the pixel value
            if ( image.at<uchar>(i,j) < threshold )
            {
                image.at<uchar>(i,j) = 0;
            }

            else
            {
                image.at<uchar>(i,j) = 255;
            }
        }
    }
    waitKey();
    return image;

}

// Function to differentiate between the image objects and the background using local thresholding
Mat local_threshold( int T_minus)
{
    //Get the dimensions of the image
    Convert_To_Gray(src,dst);
    Mat image=dst.clone();
    int rows = image.rows;
    int cols = image.cols;

    //Divide the image into smaller windows
    int window_x = rows / 3;
    int window_y = cols / 3;

    //Calculate the size of each window
    int window_dim = window_x * window_y;

    // Iterate on the pixels of the image
    for (int m=0 ; m<3 ; m++)
    {
        for(int n=0 ; n<3 ; n++)
        {
            // Initialisations
            int pixels_avg = 0;
            int pixels_sum = 0;

            // Iterate on the pixels of the window
            for (int i=window_x * m ; i<window_x*(m+1) ; i++)
            {
                for(int j=window_y*n ; j<window_y*(n+1) ; j++)
                {
                    // Calculate the summation of the pixels
                    pixels_sum = pixels_sum + image.at<uchar>(i,j);
                }
            }
            // Calculate the average of the window
            pixels_avg = pixels_sum / (window_dim);

            // Set the threshold
            int threshold = pixels_avg - T_minus;

            // Iterate on the pixels of the window
            for (int i=window_x * m ; i<window_x*(m+1) ; i++)
            {
                for (int j=window_y * n ; j<window_y*(n+1) ; j++)
                {
                    // check the pixels value
                    if ( image.at<uchar>(i,j) < threshold )
                    {
                        image.at<uchar>(i,j) = 0;
                    }
                    else
                    {
                        image.at<uchar>(i,j) = 255;
                    }
                }
            }
        }
    }
    return image;

}
/********************************************** Histogram *****************************************************/
void Histogram( int histogram[])
{
    Convert_To_Gray(src,dst);
    // initialize all intensity values to 0
    for(int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
    // calculate the no of pixels for each intensity values
    for(int y = 0; y < dst.rows; y++)
        for(int x = 0; x < dst.cols; x++)
            histogram[(int)dst.at<uchar>(y,x)]++;
}

void CumulativeHist(int histogram[], int cumhistogram[])
{
    cumhistogram[0] = histogram[0];
    for(int i = 1; i < 256; i++)
    {
        cumhistogram[i] = histogram[i] + cumhistogram[i-1];
    }
}

Mat DisplayHistogram(int histogram[])
{
    int hist[256];
    for(int i = 0; i < 256; i++)
    {
        hist[i]=histogram[i];
    }
    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);
    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));
    // find the maximum intensity element from histogram
    int max = hist[0];
    for(int i = 1; i < 256; i++){
        if(max < hist[i]){
            max = hist[i];
        }
    }
    // normalize the histogram between 0 and histImage.rows
    for(int i = 0; i < 256; i++){
        hist[i] = ((double)hist[i]/max)*histImage.rows;
    }
    // draw the intensity line for histogram
    for(int i = 0; i < 256; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h),
             Point(bin_w*(i), hist_h - hist[i]),
             Scalar(0,0,0), 1, 8, 0);
    }

    waitKey();
    return histImage;
}
Mat equalization(){
    Convert_To_Gray(src,dst);
    int histogram[256];
    Histogram(histogram);
    // Caluculate the size of image
    int size = dst.rows * dst.cols;
    float alpha = 255.0/size;
    // Calculate the probability of each intensity
    float PrRk[256];
    for(int i = 0; i < 256; i++)
    {
        PrRk[i] = (double)histogram[i] / size;
    }
    // Generate cumulative frequency histogram
    int cumhistogram[256];
    CumulativeHist(histogram,cumhistogram );
    // Scale the histogram
    int Sk[256];
    for(int i = 0; i < 256; i++)
    {
        Sk[i] = cvRound((double)cumhistogram[i] * alpha);
    }
    // Generate the equlized histogram
    float PsSk[256];
    for(int i = 0; i < 256; i++)
    {
        PsSk[i] = 0;
    }
    for(int i = 0; i < 256; i++)
    {
        PsSk[Sk[i]] += PrRk[i];
    }
    int final[256];
    for(int i = 0; i < 256; i++)
        final[i] = cvRound(PsSk[i]*255);
    // Generate the equlized image
    Mat new_image = dst.clone();
    for(int y = 0; y < dst.rows; y++)
        for(int x = 0; x < dst.cols; x++)
            new_image.at<uchar>(y,x) = saturate_cast<uchar>(Sk[dst.at<uchar>(y,x)]);
    waitKey();
    return new_image;

}

void showHistogram()
{
    int bins = 256;             // number of bins
    int nOfChannels = src.channels();    // number of channels
    cout<< nOfChannels;
    vector<Mat> hist(nOfChannels);       // histogram arrays
    // Initalize histogram arrays
    for (int i = 0; i < hist.size(); i++)
        hist[i] = Mat::zeros(1, bins, CV_32SC1);

    // Calculate the histogram of the image
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            for (int k = 0; k < nOfChannels; k++)
            {
                // determine if the number of channel is 1 -> gray or 3 -> coloured
                uchar pixel_value = nOfChannels == 1 ? src.at<uchar>(i,j) : src.at<Vec3b>(i,j)[k];
                // produce 3 histogram arrays
                hist[k].at<int>(pixel_value) += 1;
            }
        }
    }

    // For each histogram arrays, obtain the maximum (peak) value
    // Needed to normalize the display later
    int histogram_peak[3] = {0,0,0};
    for (int i = 0; i < nOfChannels; i++)
    {
        for (int j = 1; j < 256; j++)
            histogram_peak[i] = hist[i].at<int>(j) > histogram_peak[i] ? hist[i].at<int>(j) : histogram_peak[i];
        }

    const char* wname[3] = { "blue", "green", "red" };
    Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

    vector<Mat> canvas(nOfChannels);
    vector<Mat> Result(nOfChannels);

    // Display each histogram in a canvas
    for (int i = 0; i < nOfChannels; i++)
    {
        canvas[i] = Mat::ones(125, bins, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
        {
            line(
                canvas[i],
                Point(j, rows),
                Point(j, rows - (hist[i].at<int>(j) * rows/histogram_peak[i])),
                nOfChannels == 1 ? Scalar(200,200,200) : colors[i],
                1, 8, 0
            );
        }
    }
imwrite("red.jpg", canvas[0]);
imwrite("blue.jpg", canvas[1]);
imwrite("green.jpg", canvas[2]);
}
