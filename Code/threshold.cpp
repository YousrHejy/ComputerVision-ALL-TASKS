#include "threshold.h"
#include "filters.h"
using namespace std;
using namespace cv;
Mat dst4;
/********************************************** otsu *****************************************************/
// outsu's method for global optimal thresholding
Mat global_threshold_outsu ( int maxval) {
Convert_To_Gray(src,dst4);
    // Compute histogram
    int hist[256] = {0};
    for (int i = 0; i < dst4.rows; i++) {
        for (int j = 0; j < dst4.cols; j++) {
            hist[dst4.at<uchar>(i, j)]++;
        }
    }

    // Compute PDF and CDF of histogram
    double pdf[256] = {0};
    double cdf[256] = {0};
    int num_pixels = dst4.rows * dst4.cols;
    for (int i = 0; i < 256; i++) {
        pdf[i] = (double) hist[i] / num_pixels;
        if (i == 0) {
            cdf[i] = pdf[i];
        } else {
            cdf[i] = cdf[i - 1] + pdf[i];
        }
    }

    // Compute global mean intensity
    double global_mean = 0;
    for (int i = 0; i < 256; i++) {
        global_mean += i * pdf[i];
    }

    // Compute optimal threshold using Otsu's method
    double max_variance = 0;
    int threshold = 0;
    double w0, w1, u0, u1, variance;
    for (int i = 0; i < 256; i++) {
        w0 = cdf[i];
        w1 = 1 - w0;
        if (w0 == 0 || w1 == 0) {
            continue;
        }
        u0 = 0;
        for (int j = 0; j <= i; j++) {
            u0 += j * pdf[j];
        }
        u0 /= w0;
        u1 = (global_mean - w0 * u0) / w1;
        variance = w0 * w1 * pow(u0 - u1, 2);
        if (variance > max_variance) {
            max_variance = variance;
            threshold = i;
        }
    }

//     Check that the input image is grayscale
    CV_Assert(dst4.channels() == 1);

    // Create output image
    Mat dst(dst4.size(), dst4.type());

    // Apply thresholding to each pixel of the input image
    for (int i = 0; i < dst4.rows; i++) {
        for (int j = 0; j < dst4.cols; j++) {
            if (dst4.at<uchar>(i, j) >= threshold) {
                dst.at<uchar>(i, j) = maxval;
            } else {
                dst.at<uchar>(i, j) = 0;
            }
        }
    }
    Mat output = Mat::zeros(src.size(), src.type());
    output=dst;
    return output;
}
Mat adaptiveOtsuThreshold(int blockSize) {
     Convert_To_Gray(src,dst4);
    // Check that the input image is grayscale
    CV_Assert(dst4.channels() == 1);

    // Declare output image
    Mat dst(dst4.size(), dst4.type());

    // Divide the image into non-overlapping blocks
    int num_blocks_x = dst4.cols / blockSize;
    int num_blocks_y = dst4.rows / blockSize;

    // Calculate the optimal threshold for each block using Otsu's method
    for (int i = 0; i < num_blocks_y; i++) {
        for (int j = 0; j < num_blocks_x; j++) {
            // Compute block boundaries
            int x1 = j * blockSize;
            int y1 = i * blockSize;
            int x2 = min(x1 + blockSize, dst4.cols);
            int y2 = min(y1 + blockSize, dst4.rows);

            // Extract block from input image
            Mat block = dst4(Rect(x1, y1, x2 - x1, y2 - y1));

            // Compute histogram, PDF, and CDF of block
            int hist[256] = {0};
            double pdf[256] = {0};
            double cdf[256] = {0};
            int num_pixels = block.rows * block.cols;
            for (int k = 0; k < block.rows; k++) {
                for (int l = 0; l < block.cols; l++) {
                    hist[block.at<uchar>(k, l)]++;
                }
            }
            for (int k = 0; k < 256; k++) {
                pdf[k] = (double)hist[k] / num_pixels;
            }
            cdf[0] = pdf[0];
            for (int k = 1; k < 256; k++) {
                cdf[k] = cdf[k - 1] + pdf[k];
            }

            // Compute global mean and variance of block
            double global_mean = 0;
            for (int k = 0; k < 256; k++) {
                global_mean += k * pdf[k];
            }
            double global_var = 0;
            for (int k = 0; k < 256; k++) {
                global_var += pow(k - global_mean, 2) * pdf[k];
            }

            // Compute optimal threshold for block using Otsu's method
            double max_sigma = -1;
            int optimal_thresh = 0;
            double sum = 0;
            int count = 0;
            for (int k = 0; k < 256; k++) {
                sum += k * pdf[k];
                count += hist[k];
                double w1 = cdf[k];
                double w2 = 1 - w1;
                if (count == num_pixels) {
                    break;
                }
                if (w1 == 0 || w2 == 0) {
                    continue;
                }
                double mu1 = sum / count;
                double mu2 = (global_mean - sum) / (num_pixels - count);
                double sigma = w1 * w2 * pow(mu1 - mu2, 2);
                if (sigma > max_sigma) {
                    max_sigma = sigma;
                    optimal_thresh = k;
                }
            }

            // Apply thresholding to block
            for (int k = y1; k < y2; k++) {
                for (int l = x1; l < x2; l++) {
                    if (dst4.at<uchar>(k, l) >= optimal_thresh) {
                        dst.at<uchar>(k, l) = 255;
                    } else {
                        dst.at<uchar>(k, l) = 0;
                    }
                }
            }
        }
    }

    // Return output image
    return dst;
}
/********************************************** itterative *****************************************************/
void threshold_manual(const Mat& src, Mat& dst, double thresh, double maxval, int type) {
    // Check that the input and output images have the same size and type
    CV_Assert(src.size() == dst.size() && src.type() == dst.type());

    // Apply thresholding operation to each pixel
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            double pixel = src.at<uchar>(i, j);
            switch (type) {
                case THRESH_BINARY:
                    dst.at<uchar>(i, j) = (pixel > thresh) ? maxval : 0.0;
                    break;
                case THRESH_BINARY_INV:
                    dst.at<uchar>(i, j) = (pixel > thresh) ? 0.0 : maxval;
                    break;
                default:
                    cerr << "Error: Unsupported thresholding type\n";
                    return;
            }
        }
    }
}
Mat iterativeGlobalThresholding( double epsilon) {
    Convert_To_Gray(src,dst4);
    // Check that the input image is grayscale
    CV_Assert(dst4.channels() == 1);

    // Declare output image
    Mat dst(dst4.size(), dst4.type());

    // Initialize the threshold value to the average intensity of the input image
    double thresh = mean(dst4)[0];

    // Initialize the old threshold value to zero
    double oldThresh = 0.0;

    // Iterate until the difference between the old and new threshold values is less than epsilon
    while (abs(thresh - oldThresh) > epsilon) {
        // Compute the mean intensities of foreground and background pixels
        double fgSum = 0.0, bgSum = 0.0;
        int fgCount = 0, bgCount = 0;
        for (int i = 0; i < dst4.rows; i++) {
            for (int j = 0; j < dst4.cols; j++) {
                double pixel = dst4.at<uchar>(i, j);
                if (pixel > thresh) {
                    fgSum += pixel;
                    fgCount++;
                } else {
                    bgSum += pixel;
                    bgCount++;
                }
            }
        }
        double fgMean = (fgCount > 0) ? fgSum / fgCount : 0.0;
        double bgMean = (bgCount > 0) ? bgSum / bgCount : 0.0;

        // Update the threshold value as the average of foreground and background mean intensities
        oldThresh = thresh;
        thresh = (fgMean + bgMean) / 2.0;

        // Apply threshold to input image and store the result in output image
        threshold_manual(dst4, dst, thresh, 255.0, THRESH_BINARY);
    }

    // Return output image
    return dst;
}

Mat iterativeLocalThresholding( int blockSize, double epsilon) {
    // Check that the input image is grayscale
    Convert_To_Gray(src,dst4);
    CV_Assert(dst4.channels() == 1);

    // Create output image
    dst.create(dst4.size(), dst.type());

    // Initialize threshold value
    double threshold = mean(src)[0];

    // Iterate until convergence
    while (true) {
        // Calculate mean values of foreground and background pixels
        Scalar fgMean, bgMean;
        threshold_manual(dst4, dst, threshold, 255, THRESH_BINARY);
        fgMean = mean(dst4, dst);
        bgMean = mean(dst4, ~dst);

        // Calculate new threshold value
        double newThreshold = 0.5 * (fgMean[0] + bgMean[0]);

        // Check for convergence
        if (abs(newThreshold - threshold) < epsilon) {
            break;
        }

        // Update threshold value
        threshold = newThreshold;
    }
    Mat out=Mat::zeros(dst4.size(), dst4.type());
    out=dst;
    return out;
}
/********************************************** spectral *****************************************************/
Mat spectral_threshold(Mat image) {
    Mat blur;
    GaussianBlur(image, blur, Size(5, 5), 0);

    Mat hist;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    int histSize[] = { 256 };
    int channels[] = { 0 };
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, &histRange);

    hist /= sum(hist)[0];

    Mat BetweenClassVarsList(256, 256, CV_64F, Scalar(0));
    for (int bar1 = 0; bar1 < hist.rows; bar1++) {
        for (int bar2 = bar1; bar2 < hist.rows; bar2++) {
            vector<int> foregroundLevels;
            vector<int> backgroundLevels;
            vector<int> midgroundLevels;
            vector<float> foregroundHist;
            vector<float> backgroundHist;
            vector<float> midgroundHist;
            for (int level = 0; level < hist.rows; level++) {
                if (level < bar1) {
                    backgroundLevels.push_back(level);
                    backgroundHist.push_back(hist.at<float>(level));
                }
                else if (level > bar1 && level < bar2) {
                    midgroundLevels.push_back(level);
                    midgroundHist.push_back(hist.at<float>(level));
                }
                else {
                    foregroundLevels.push_back(level);
                    foregroundHist.push_back(hist.at<float>(level));
                }
            }
            float FWeights = 0.0;
            float BWeights = 0.0;
            float MWeights = 0.0;
            float f=0.0;
            float b=0.0;
            float m=0.0;
            for (int i = 0; i < foregroundHist.size(); i++) {
                FWeights += foregroundHist[i];
            }

            for (int i = 0; i < backgroundHist.size(); i++) {
                BWeights += backgroundHist[i];
            }

            for (int i = 0; i < midgroundHist.size(); i++) {
                MWeights += midgroundHist[i];
            }

            f =FWeights/ sum(hist)[0];
            b =BWeights/ sum(hist)[0];
            m= MWeights/sum(hist)[0];
            float FMean = 0.0;
            float BMean = 0.0;
            float MMean = 0.0;

            for (int i = 0; i < foregroundHist.size(); i++) {
                FMean += foregroundHist[i] * foregroundLevels[i];
            }

            for (int i = 0; i < backgroundHist.size(); i++) {
                BMean += backgroundHist[i] * backgroundLevels[i];
            }

            for (int i = 0; i < midgroundHist.size(); i++) {
                MMean += midgroundHist[i] * midgroundLevels[i];
            }

            FMean /= FWeights;
            BMean /= BWeights;
            MMean /= MWeights;

            float BetClsVar = f * b * pow((BMean - FMean), 2) + \
                  f * m * pow((FMean - MMean), 2) + \
                 b * m * pow((BMean - MMean), 2);
            BetweenClassVarsList.at<double>(bar1, bar2) = BetClsVar;
        }
    }

    double max_value;
    cv::minMaxLoc(BetweenClassVarsList, nullptr, &max_value);
    Mat threshold_indices;
    cv::findNonZero(BetweenClassVarsList == max_value, threshold_indices);
return threshold_indices;
}
Mat global(){
     Convert_To_Gray(src,dst4);
    Mat threshold_indices= spectral_threshold(dst4);
    int row = threshold_indices.at<int>(0, 0);
    int col = threshold_indices.at<int>(0, 1);

    Mat thresh_img(dst4.rows, dst4.cols, CV_8UC1);
    for (int r = 0; r < dst4.rows; r++) {
        for (int c = 0; c < dst4.cols; c++) {
            if (dst4.at<uint8_t>(r, c) >col){
                thresh_img.at<uint8_t>(r, c) = 255;
            }
            else if (dst4.at<uint8_t>(r, c) <row)  {
                thresh_img.at<uint8_t>(r, c) = 0;
            }
            else {
                thresh_img.at<uint8_t>(r, c) = 128;
            }
        }
    }

    return thresh_img;
}
