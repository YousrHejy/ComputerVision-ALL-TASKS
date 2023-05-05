#include "filters.h"
/********************************************** Gray *****************************************************/
/* convert colored image to gray scale*/
void Convert_To_Gray(const Mat &src, Mat &dst)    // func convert to gray
{

    int rows = src.rows, cols = src.cols;

    dst.create(src.size(), 0);

    cols = rows * cols;
    rows = 1;

    for (int row = 0; row < rows; row++)
    {
        const uchar* src_ptr = src.ptr<uchar>(row);
        uchar* dst_ptr = dst.ptr<uchar>(row);

        for (int col = 0; col < cols; col++)
        {
            dst_ptr[col] = (uchar)(src_ptr[0] * 0.114f + src_ptr[1] * 0.587f + src_ptr[2] * 0.299f);
            src_ptr += 3;
        }
    }
}
/********************************************** Noise *****************************************************/
// guasian Noise
Mat gaussin_noise(){
     Convert_To_Gray(src,dst);
    // Let's first create a zero image with the same dimensions of the loaded image
    Mat gaussian_noise = Mat::zeros (dst.rows, dst.cols, CV_8UC1);
    // now, we can set the pixel values as a Gaussian noise
    // we have set a mean value to 128 and a standard deviation to 20
    randn(gaussian_noise, 128, 20);
    imwrite("Result.jpg", gaussian_noise);
    return gaussian_noise;
}
// Uniform Noise
Mat uniform_noise(){
    Convert_To_Gray(src,dst);
    Mat uniform_noise = cv::Mat::zeros (dst.rows, dst.cols, CV_8UC1);
    randu(uniform_noise, 0, 255);
    imwrite("Uniform random noise.jpg", uniform_noise);
    return uniform_noise;
}
// Salt and peper noise
Mat spl(){
    Convert_To_Gray(src,dst);
    Mat saltpepper_noise = Mat::zeros(dst.rows, dst.cols,CV_8U);
    randu(saltpepper_noise,0,255);
    Mat black = saltpepper_noise < index2;
    Mat white = saltpepper_noise > (255-index2);
    Mat saltpepper_img = dst.clone();
    saltpepper_img.setTo(255,white);
    saltpepper_img.setTo(0,black);
    waitKey();
    return saltpepper_img;
}
Mat output_gaussin(){
    Convert_To_Gray(src,dst);
    Mat noisy_image=dst.clone();
    Mat gaussin_noise1=gaussin_noise();
    // note that we can simply sum two Mat objects, that is, two images.
    // in order not to degrade the image quality too much
    // we will multipliy the gaussian_noise with 0.5.
    // in this way the effect of noise will be reduced
    noisy_image = dst + gaussin_noise1.mul(index1);

    waitKey();
    return noisy_image;
}

Mat output_uniform(){
    Convert_To_Gray(src,dst);
    Mat noisy_image=dst.clone();
    Mat uniform_noise1=uniform_noise();
    // note that we can simply sum two Mat objects, that is, two images.
    // in order not to degrade the image quality too much
    // we will multipliy the gaussian_noise with 0.5.
    // in this way the effect of noise will be reduced
    noisy_image = dst + uniform_noise1.mul(index3);
    cv::waitKey();

    return noisy_image;
}

/********************************************** Filters *****************************************************/
/********************************************** Low pass *****************************************************/
/*function to apply convelution between two matrices that have different sizes*/
Mat conv (Mat &image,int rows,int columns,int width,int height,int r,Mat &mask){
    Mat filtered_image=Mat(rows ,columns, CV_8UC1, Scalar(0, 0, 0));
    for(int y=r;y<rows-r;++y){
        for(int x=r;x<columns-r;++x) {
            for(int i=0;i<width;++i){
                for(int j=0;j<height;j++){
                    filtered_image.at<uchar>(y,x)+=(image.at<uchar>(y+i-r, x+j-r)*mask.at<float>(i,j) );
                }
            }
        }
    }
    return filtered_image;
}
/*function to create guasian filter*/
Mat filter_create(int width ,int height,int shift) {
    int sigma = 1;
    float r, s = 2.0 * sigma * sigma;
    // sum is for normalization
    float sum = 0.0;
    Mat mask = Mat(width, height, CV_32F);
    //shift calculate form w,h =root((2r+1)^2)
    for (int x = -shift; x <= shift; x++) {
        for (int y = -shift; y <= shift; y++) {
            r = sqrt(x * x + y * y);
            mask.at<float>(x+shift,y+shift) = (exp(-(r * r) / s)) / (M_PI * s);
            sum +=  mask.at<float>(x+shift,y+shift) ;
        }
    }
    // normalising the Kernel
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            mask.at<float>(i,j) /= sum;
}}
    return mask;
}
/*function to apply guasian filter on image*/
Mat guasian_filter(int size){
    Convert_To_Gray(src,dst);
    int width =sqrt(size);
    int height =sqrt(size);
    int radius=ceil(float (width-1)/2);
    int rows = dst.rows;
    int columns = dst.cols;
    Mat mask_g = Mat(width, height, CV_32F);
    mask_g =filter_create( width ,height,radius);
    Mat result_image= conv(dst,rows,columns, width,height, radius,mask_g);
    waitKey();
    return result_image;
}

/*function to apply mean filter on image*/
Mat mean_filter(int size){
    Convert_To_Gray(src,dst);
    int width =sqrt(size);
    int height =sqrt(size);
    int radius=ceil(float (width-1)/2);
    int rows = dst.rows;
    int columns = dst.cols;
    Mat mask = Mat(width,height, CV_32F, Scalar(1));
    mask=mask/(width*height);
    Mat result_image=conv (dst,rows,columns, width,height, radius,mask);
    waitKey();
    return result_image;
}
/*function to apply mean  filter on image that depend on sorting element of kernal */
Mat median_filter(int size){
    Convert_To_Gray(src,dst);
    int width =sqrt(size);
    int height =sqrt(size);
    int r=ceil(float (width-1)/2);
    vector<uchar> v(size, 1);
    int rows = dst.rows;
    int columns = dst.cols;
    Mat filtered_image = Mat(rows, columns, CV_8UC1);
    for (int y = r; y < rows - r; ++y) {
        for (int x = r; x < columns - r; ++x) {
            int m=0;
            for (int i = 0; i< width ; ++i) {
                for (int j=0;j<height; ++j){
                    v[m] = dst.at<uchar>(y+i - r, x+j-r);
                    m++;
                }
            }
            std::sort(v.begin(), v.end());
            filtered_image.at<uchar>(y, x) = v[int(ceil ((size-1)/2) )];
        }
    }
    Mat output;
    waitKey();
    return filtered_image;
}
/********************************************** High pass *****************************************************/
Mat filters( float  x[] ,  float  y[],int row , int col){
    Convert_To_Gray(src,dst);
    Mat data_x,data_y,result;
    Mat filter_x =Mat(row,col,CV_32F,x);
    Mat filter_y =Mat(row,col,CV_32F,y);
    filter2D(dst, data_x, -1 ,filter_x);
    filter2D(dst, data_y, -1 ,filter_y);
    data_x.convertTo(data_x,CV_32F);
    data_y.convertTo(data_y,CV_32F);
    magnitude(data_x,data_y,result);
    result.convertTo(result,CV_8UC1);
    waitKey();
    return result;
}
