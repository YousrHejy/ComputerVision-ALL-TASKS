#include "halfdetection.h"
#include "filters.h"
// Declaring some constants for the parameters
int r = 1;
double theta = CV_PI/180;
/**************************************** HoughLines ***************************************/
Mat DrawHoughLines(vector<Vec2f> lines,Mat orginalImageWithHoughLines){

    for (size_t i = 0; i < lines.size(); i++)
    {
        Point pt1, pt2;
        double a, b, x0, y0;
        float rho = lines[i][0];
        float theta = lines[i][1];
        a = cos(theta), b = sin(theta);
        x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(orginalImageWithHoughLines, pt1, pt2, Scalar(0,0,255), 2, LINE_AA);
    }
    return orginalImageWithHoughLines;
}

Mat houghLines( int minDist, double minAngle, int threshold)
{
    Mat edges;
    Convert_To_Gray(src,dst);
    Canny(dst, edges, 100, 200, 3);
    int rows, cols, numRho, numTheta;
    double maxDist, dTheta;
    rows = edges.rows;
    cols = edges.cols;

    maxDist = sqrt(rows*rows + cols*cols);
    numRho = cvRound(maxDist/minDist);

    dTheta = minAngle;
    numTheta = cvRound(CV_PI/dTheta);

    vector<int> accumulator(numTheta*numRho, 0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (edges.at<uchar>(i, j) > 0)
            {
                for (int t = 0; t < numTheta; t++)
                {
                    double theta = t*dTheta;
                    double rho = j*cos(theta) + i*sin(theta);
                    int rhoIdx = cvRound(rho/minDist + numRho/2);
                    accumulator[(t*numRho) + rhoIdx]++;
                }
            }
        }
    }

    vector<Vec2f> lines;
    for (int t = 0; t < numTheta; t++)
    {
        for (int r = 0; r < numRho; r++)
        {
            int idx = t*numRho + r;
            if (accumulator[idx] >= threshold)
            {
                double rho = (r - numRho/2)*minDist;
                double theta = t*dTheta;
                lines.push_back(Vec2f(rho, theta));
            }
        }
    }

    Mat result= DrawHoughLines( lines,src);
    return result;
}
/**************************************** HoughCircles ***************************************/
Mat detectEllipses_circle(float threshold)
{
    Convert_To_Gray(src,dst);
    Mat image, grayImage, edgeImage;
    vector<vector<Point>> contours;
    vector<RotatedRect> shapes;
    // Apply canny edge detection
    Canny(dst, edgeImage, 50, 100, 3);
    // Find contours
    findContours(edgeImage, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    // Fit ellipses to contours
    for (size_t i = 0; i < contours.size(); i++)
    {
        if (contours[i].size() >= 5)
        {
            RotatedRect shape = fitEllipse(contours[i]);
            double score = fabs(1 - (double)shape.size.width / shape.size.height);
            if (score < threshold)
            {
                shapes.push_back(shape);
            }
        }
    }
    // Draw ellipses on the image
    Mat finalDetectedImage = src.clone();
    for (size_t i = 0; i < shapes.size(); i++)
    {
        ellipse(finalDetectedImage, shapes[i], Scalar(0,255,0), 3, LINE_AA);
    }
    return finalDetectedImage;
}
/**************************************** HoughTriangle ***************************************/
Mat detect_triangle(){
    Mat gray;
    Convert_To_Gray(src,dst);
    vector<vector<Point>> triangles;
    vector<Vec4i> hierarchy;
    Canny(dst, gray, 50, 200, 3);
    findContours(gray, triangles, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> filtered_triangles;
    for (int i = 0; i < triangles.size(); i++) {
        vector<Point> approx;
        approxPolyDP(triangles[i], approx, arcLength(triangles[i], true) * 0.02, true);
        if (approx.size() == 3) {
            filtered_triangles.push_back(approx);
        }
    }

    for (int i = 0; i < triangles.size(); i++) {
        const Point* vertices[1] = { &triangles[i][0] };
        int nvertices[] = { (int)triangles[i].size() };
        polylines(src, vertices, nvertices, 1, true, Scalar(0, 0, 255), 3, LINE_AA);
    }

    return src;
}

