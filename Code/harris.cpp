#include "harris.h"
#include "filters.h"
Mat find_harris_corners(double k, int window_size, double threshold) {
    Convert_To_Gray(src,dst);
    vector<vector<double>> corner_list;
    Mat output_img;
    int up_width = 300;
    int up_height = 300;
    Mat resized_up=dst;
    resize(dst,resized_up, Size(up_width, up_height), INTER_LINEAR);
    cvtColor(resized_up, output_img, COLOR_GRAY2RGB);

    int offset = window_size / 2;
    int y_range =resized_up.rows - offset;
    int x_range = resized_up.cols - offset;

    Mat dx, dy;
    Sobel(resized_up, dx, CV_64F, 1, 0, 3);
    Sobel(resized_up, dy, CV_64F, 0, 1, 3);
    Mat Ixx = dx.mul(dx);
    Mat Ixy = dx.mul(dy);
    Mat Iyy = dy.mul(dy);

    for (int y = offset; y < y_range; y++) {  //iterates through each pixel in the image and computes the Harris corner response
        for (int x = offset; x < x_range; x++) {
            // Values of sliding window
            int start_y = y - offset;
            int end_y = y + offset + 1;
            int start_x = x - offset;
            int end_x = x + offset + 1;


            // the variable of the Harris corner equation
            Mat windowIxx = Ixx(Rect(start_x, start_y, window_size, window_size));
            Mat windowIxy = Ixy(Rect(start_x, start_y, window_size, window_size));
            Mat windowIyy = Iyy(Rect(start_x, start_y, window_size, window_size));

            // Sum of squares of intensities of partial derivatives
            double Sxx = sum(windowIxx)[0];
            double Sxy = sum(windowIxy)[0];
            double Syy = sum(windowIyy)[0];

            // Calculate determinant and trace of the matrix
            double det = (Sxx * Syy) - (Sxy * Sxy);
            double trace = Sxx + Syy;

            // Calculate r for Harris Corner equation
            double r = det - k * (trace * trace);

            if (r > threshold) {
                corner_list.push_back({(double)x, (double)y, r});
                output_img.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
            }
        }
    }

    return  output_img;
}
