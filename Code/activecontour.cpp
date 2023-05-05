#include "activecontour.h"
#include "filters.h"
// internal forces = summation from i to n alpha * |Vi+1 - Vi|2 + beta * |Vi+1 - 2* Vi + Vi-1 |2
double internalEnergy(const vector<Point>& snake , float alpha , int beta) {
    double iEnergy = 0;
    int snakeLength = snake.size();
    for (int index = snakeLength - 1; index >= 0; index--) {
        int nextPoint = (index + 1) % snakeLength;
        int currentPoint = index % snakeLength;
        int previousePoint = (index - 1 + snakeLength) % snakeLength;
        iEnergy = iEnergy + (alpha * pow(norm(snake[nextPoint] - snake[currentPoint]), 2)) \
                          + (beta * pow(norm(snake[nextPoint] - 2 * snake[currentPoint] + snake[previousePoint]), 2));
    }
    return iEnergy;
}

// total energy for internal and external without constant
double totalEnergy(const Mat& grediant, const Mat& image, const vector<Point>& snake , float alpha , int beta , int gamma) {
    double iEnergy = internalEnergy(snake , alpha , beta);
    double eEnergy = externalEnergy(grediant , image , snake , gamma);
    return iEnergy + eEnergy;
}

// external forces summation of image gradient for all contour points
double externalEnergy(const Mat& gradient, const Mat& image, const vector<Point>& snake , int gamma) {
    double eEnergy = 0;
    int snaxels_Len = snake.size();
    for (int index = 0; index < snaxels_Len; index++)
    {
        Point point = snake[index];
        eEnergy += (gamma * 10 * image.at<uchar>(point)) - (gamma * 10 * gradient.at<uchar>(point));
    }
    return eEnergy;
}

Mat basicImageGradient(const Mat& image)
{
    Mat sobelx, sobely, gradient;
    Sobel(image, sobelx, CV_64F, 1, 0);
    Sobel(image, sobely, CV_64F, 0, 1);
    sobelx = abs(sobelx);
    sobely = abs(sobely);
    sobelx.convertTo(sobelx, CV_8U);
    sobely.convertTo(sobely, CV_8U);
    addWeighted(sobelx, 0.5, sobely, 0.5, 1, gradient);
    return gradient;
}

bool isPointInsideImage(const Mat& image, const Point& point) {
    return (point.x >= 0 && point.x < image.cols && point.y >= 0 && point.y < image.rows);
}

// returns an array of points on a circle with given center and radius
vector<Point> pointsOnCircle(Point center, int radius, int num_points) {
    vector<Point> points(num_points);
    for (int i = 0; i < num_points; i++) {
        double theta = double(i) / num_points * (2 * CV_PI);
        int x = center.x + radius * cos(theta);
        int y = center.y + radius * sin(theta);
        points[i] = Point(x, y);
    }
    return points;
}

// active contour implementation using the snake algorithm
Mat activeContour( int radius , float alpha , int beta , int gamma)
{
    Convert_To_Gray(src,dst);
    Point center(dst.cols/2 , dst.rows/2);
//    namedWindow("Active Contour", WINDOW_NORMAL);
//    resizeWindow("Active Contour", Size(dst.cols, dst.rows));
    vector<Point> snake = pointsOnCircle(center, radius, radius/2);
    Mat gradient = basicImageGradient(dst);
    vector<Point> snakeColon = snake;

    for (int i = 0; i < 100; i++) {
        for (size_t index = 0; index < snake.size(); index++) {
            double min_energy2 = numeric_limits<double>::infinity();
            int indexOFlessEnergy;
            for (size_t cindex = 0; cindex < NUM_NEIGHBORS; cindex++) {
                Point movement = Point(neighbors[cindex][0], neighbors[cindex][1]);
                Point next_node = snake[index] + movement;
                if (!isPointInsideImage(dst, next_node) || !isPointInsideImage(dst, snake[index])) {
                    continue;
                }

                snakeColon[index] = next_node;
                double totalEnergyNext = totalEnergy(gradient, dst, snakeColon, alpha , beta , gamma);

                if (totalEnergyNext < min_energy2)
                {
                    min_energy2 = totalEnergyNext;
                    indexOFlessEnergy = cindex;
                    snake[index] += Point(neighbors[indexOFlessEnergy][0], neighbors[indexOFlessEnergy][1]);
                }
            }
        }
        snakeColon = snake;
    }
    if (!snake.empty())
    {
        // Create a vector of points to draw the contour line
        vector<Point> contour(snake.size() + 1);
        for (size_t i = 0; i < snake.size(); i++) {
            contour[i] = snake[i];
        }
        contour.back() = snake.front();

        // Draw the contour line on the image
        polylines(src, contour, false, Scalar(255, 0, 0), 3);
    }
    return src;
}
\
