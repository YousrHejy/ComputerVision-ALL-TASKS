#include "frequency.h"
#include "filters.h"
Mat dst2;
/********************************************** Frequency domain *****************************************************/
/* Convert from time domain to frequency domain */
Mat calculateDFt(Mat &img){
    Mat padded;
    int m = getOptimalDFTSize( img.rows );
    int n = getOptimalDFTSize( img.cols ); // on the border add zero values
    copyMakeBorder(img, padded, 0, m - img.rows, 0, n - img.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complex;
    merge(planes, 2, complex);         // Add to the expanded another plane with zeros
    dft(complex, complex, DFT_COMPLEX_OUTPUT);
    return complex;
}
/* use to return image to correct its place */
void fftShift(Mat &imgComplex) {
    // crop if it has an odd number of rows or columns
    imgComplex= imgComplex(Rect(0, 0, imgComplex.cols & -2, imgComplex.rows & -2));
    int cx = imgComplex.cols/2;
    int cy = imgComplex.rows/2;
    Mat q0(imgComplex, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(imgComplex, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(imgComplex, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(imgComplex, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat pos;                            // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(pos);
    q3.copyTo(q0);
    pos.copyTo(q3);
    q1.copyTo(pos);                     // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    pos.copyTo(q2);
}
/********************************************** filters *****************************************************/
/* generate image filter in frequency domain high or low pass filtering
 *  depend on flag sent */
void filterImage(const cv::Mat &dft_Filter, int radius,int filterType)
{
    Mat tmp = Mat(dft_Filter.rows, dft_Filter.cols, CV_32F);

    Point centre = Point(dft_Filter.rows / 2, dft_Filter.cols / 2);
    double distance;

    for(int i = 0; i < dft_Filter.rows; i++)
    {
        for(int j = 0; j < dft_Filter.cols; j++)
        {
            distance = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
            if(distance>radius){
                if(filterType==0){
                    tmp.at<float>(i,j) = (float)0;
                }else {
                    tmp.at<float>(i, j) = (float) 1;
                }
            }else{
                if(filterType==0){
                    tmp.at<float>(i,j) = (float)1;
                }else{
                    tmp.at<float>(i,j) = (float)0;
                }
            }

        }
    }

    Mat toMerge[] = {tmp, tmp};
    merge(toMerge, 2, dft_Filter);
}
/********************************************** operations on image *****************************************************/
/*image filtering */
Mat fft_image(Mat &img,int type,int radius){
    Mat complexImg, filter;
    complexImg = calculateDFt(img);
    filter = complexImg.clone();
    filterImage(filter, radius,type);
    fftShift(complexImg);
    mulSpectrums(complexImg, filter, complexImg, 1); // multiply 2 spectrums
    return complexImg;
}
/*change filtered image from frequency domain to time domain */
Mat return_image(int type,int radius){
    Convert_To_Gray(src,dst);
    Mat imgOutput, planes[2];
    Mat complexImg=fft_image(dst,type,radius);
    fftShift(complexImg); // rearrange quadrants
    // compute inverse
    idft(complexImg, complexImg);
    split(complexImg, planes);
    normalize(planes[0], imgOutput, 0, 1,cv::NORM_MINMAX);
    waitKey();
    return imgOutput;
}
/*hyprid image  */
Mat hyprid(int radius){
    Convert_To_Gray(src,dst);
    Convert_To_Gray(src2,dst2);
    Mat image1=dst.clone();
    Mat image2=dst2.clone();
    Mat DFT_image1, DFT_image2,  sum, planes[2], result;
    DFT_image1=fft_image(dst,0,radius);
    DFT_image2=fft_image(dst2,1,radius);
    sum = DFT_image1 + DFT_image2;
    fftShift(sum);
    // compute inverse
    idft(sum, sum);
    split(sum, planes);
    normalize(planes[0], result, 0, 1,cv::NORM_MINMAX);
    waitKey();
    return result;
}
