#include "segmatation.h"
#include "mainwindow.h"

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <random>
#include "filters.h"
Mat dst5;
/********************************************** kmean *****************************************************/

double euclidean_distance(const Vec3b& a, const Vec3b& b) {
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
}

Mat kmeans_segmentation_custom( int k, int max_iterations ) {
    if (k < 2) {
        cerr << "Error: Number of clusters must be at least 2." << endl;
        return Mat();
    }
    if (src.empty()) {
        cerr << "Error: Could not load image." << endl;
        return Mat();
    }
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(0, src.rows * src.cols - 1);
    Mat pixels = src.reshape(1, src.rows * src.cols);
    Mat labels(pixels.size(), CV_32SC1);
    for (int i = 0; i < pixels.rows; i++) {
        labels.at<int>(i) = -1;
    }
    vector<Vec3f> centroids(k);
    for (int i = 0; i < k; i++) {
        centroids[i] = pixels.at<Vec3b>(dist(rng), 0);
    }
    bool converged = false;
    for (int iter = 0; iter < max_iterations && !converged; iter++) {
        vector<Vec3f> new_centroids(k, Vec3f(0, 0, 0));
        vector<int> cluster_sizes(k, 0);
        for (int i = 0; i < pixels.rows; i++) {
            double min_dist = numeric_limits<double>::max();
            int cluster = -1;
            for (int j = 0; j < k; j++) {
                double dist = euclidean_distance(pixels.at<Vec3b>(i, 0), centroids[j]);
            if (dist < min_dist) {
                min_dist = dist;
                cluster = j;
            }
        }
        if (cluster != -1) {
            labels.at<int>(i) = cluster;
            new_centroids[cluster] += pixels.at<Vec3b>(i, 0);
            cluster_sizes[cluster]++;
        }
    }
    for (int j = 0; j < k; j++) {
        if (cluster_sizes[j] > 0) {
            new_centroids[j] /= cluster_sizes[j];
        }
        else {
            new_centroids[j] = pixels.at<Vec3b>(dist(rng), 0);
        }
    }
    converged = true;
    for (int j = 0; j < k; j++) {
        if (euclidean_distance(centroids[j], new_centroids[j]) > 1e-6) {
            converged = false;
            break;
        }
    }
    centroids = new_centroids;
}
Mat out = src.clone();
for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
        int label = labels.at<int>(i * src.cols + j);
        out.at<Vec3b>(i, j) = centroids[label];
    }
}
return out;
}
/********************************************** Mean shift *****************************************************/

void point_lab(Point5D& pt) {
    /* LAB Color Space Equation */
    pt.l = pt.l * 100 / 255;
    pt.a = pt.a - 128;
    pt.b = pt.b - 128;
}

void point_rgb(Point5D& pt) {
    /* RGB Color Space Equation */
    pt.l = pt.l * 255 / 100;
    pt.a = pt.a + 128;
    pt.b = pt.b + 128;
}

void point_accum(Point5D& pt1, const Point5D& pt2) {
    pt1.x += pt2.x;
    pt1.y += pt2.y;
    pt1.l += pt2.l;
    pt1.a += pt2.a;
    pt1.b += pt2.b;
}

void point_copy(Point5D& pt1, const Point5D& pt2) {
    pt1.x = pt2.x;
    pt1.y = pt2.y;
    pt1.l = pt2.l;
    pt1.a = pt2.a;
    pt1.b = pt2.b;
}

float point_color_distance(const Point5D& pt1, const Point5D& pt2) {
    return sqrt((pt1.l - pt2.l) * (pt1.l - pt2.l) + (pt1.a - pt2.a) * (pt1.a - pt2.a) + (pt1.b - pt2.b) * (pt1.b - pt2.b));
}

float point_spatial_distance(const Point5D& pt1, const Point5D& pt2) {
    return sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
}

void point_scale(Point5D& pt, float scale) {
    pt.x *= scale;
    pt.y *= scale;
    pt.l *= scale;
    pt.a *= scale;
    pt.b *= scale;
}

void point_set(Point5D& pt, float px, float py, float pl, float pa, float pb) {
    pt.x = px;
    pt.y = py;
    pt.l = pl;
    pt.a = pa;
    pt.b = pb;
}

Mat mean_shift_segmentation( float spatial_bandwidth, float color_bandwidth) {
    Mat filtered_img, output(src.size(), src.type());
    src.copyTo(filtered_img);

    int rows = src.rows;
    int cols = src.cols;
    vector<Mat> img_channels;
    split(filtered_img, img_channels);

    Point5D pt_cur, pt_prev, pt_sum, pt;
    int left, right, top, bottom, num_pts, step;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            left = (j - spatial_bandwidth) > 0 ? (j - spatial_bandwidth) : 0;
            right = (j + spatial_bandwidth) < cols ? (j + spatial_bandwidth) : cols;
            top = (i - spatial_bandwidth) > 0 ? (i - spatial_bandwidth) : 0;
            bottom = (i + spatial_bandwidth) < rows ? (i + spatial_bandwidth) : rows;

            point_set(pt_cur, i, j, (float)img_channels[0].at<uchar>(i, j), (float)img_channels[1].at<uchar>(i, j), (float)img_channels[2].at<uchar>(i, j));
            point_lab(pt_cur);
            point_copy(pt_prev, pt_cur);

            step = 0;
            while (step < 10)
            {
                point_set(pt_sum, 0, 0, 0, 0, 0);
                num_pts = 0;

                for (int ii = top; ii < bottom; ii++) {
                    for (int jj = left; jj < right; jj++) {
                        point_set(pt, ii, jj, (float)img_channels[0].at<uchar>(ii, jj), (float)img_channels[1].at<uchar>(ii, jj), (float)img_channels[2].at<uchar>(ii, jj));
                        point_lab(pt);

                        if (point_spatial_distance(pt, pt_cur) <= spatial_bandwidth && point_color_distance(pt, pt_cur) <= color_bandwidth) {
                            point_accum(pt_sum, pt);
                            num_pts++;
                        }
                    }
                }

                if (num_pts == 0) {
                    /* No points within the bandwidth, convergence reached */
                    break;
                }

                point_scale(pt_sum, 1.0 / num_pts);
                point_copy(pt_prev, pt_cur);
                point_copy(pt_cur, pt_sum);

                if (point_spatial_distance(pt_cur, pt_prev) <= 0.6) {
                    /* Convergence reached */
                    break;
                }

                step++;
            }

            /* Assign the pixel to the cluster represented by the converged point */
            point_rgb(pt_cur);
            output.at<Vec3b>(i, j)[0] = (uchar)pt_cur.l;
            output.at<Vec3b>(i, j)[1] = (uchar)pt_cur.a;
            output.at<Vec3b>(i, j)[2] = (uchar)pt_cur.b;
        }
    }

    return output;
}

void region_growing_segmentation(Mat &image,Mat output_image, Point seed, float threshold, char color_flag) {
//    Mat output_image;
    queue<Point> q_segmented_points;
    // Initialize region vector
    vector<Point> segmented_region;
    Point current_point;
    float x_current, y_current;
    // Initialize visited matrix to zeros
    Mat visited_mat = Mat::zeros(image.size(), CV_8U);

    // the first part in the regoin
    q_segmented_points.push(seed);
    while (!q_segmented_points.empty()) {
        // as long as the queue contain points
        // pop each point and finf the points that belongs to this regoin
        // if the similarity matches, add it to the regoin vector
        current_point = q_segmented_points.front();
        x_current = current_point.x;
        y_current = current_point.y;
        q_segmented_points.pop();
        // check if the point is checked before or not
        if (visited_mat.at<uchar>(y_current, x_current) != 0) {
            continue;
        }
        // if not -> add the current point to visited matrix
        visited_mat.at<uchar>(y_current, x_current) = 255;

        // coloured now
//        if (abs(image.at<float>(y_current, x_current) - image.at<float>(seed.y, seed.x)) < threshold) {
        if (norm(image.at<Vec3f>(y_current, x_current), image.at<Vec3f>(seed.y, seed.x)) < threshold) {
            segmented_region.push_back(current_point);
            if (y_current > 0) {
                q_segmented_points.push(Point(current_point.x, y_current - 1));
            }
            if (x_current > 0) {
                q_segmented_points.push(Point(x_current - 1, y_current));
            }
            if (y_current < image.rows - 1) {
                q_segmented_points.push(Point(x_current, y_current + 1));
            }
            if (x_current < image.cols - 1) {
                q_segmented_points.push(Point(x_current + 1, y_current));
            }
        }
    }

    // draw the segmented part on the input image
    for (Point p : segmented_region) {
        output_image.at<Vec3b>(p.y, p.x) = Vec3b(0, 0, 255);
    }
    // Save output image
//    imwrite("output.jpg", output_image);
//    return output_ima/ge;
}
Mat gray( Point seed, float threshold, char color_flag){
     Convert_To_Gray(src,dst5);
    Mat float_image,output_image;
    // Convert image to float for better precision
    resize(dst5, dst5, Size(256, 256));
    dst5.convertTo(float_image, CV_32F);
    // Create output image and color segmented region in red
    cvtColor(dst5, output_image, COLOR_GRAY2BGR);
    // Perform region growing segmentation
   region_growing_segmentation(float_image,output_image, seed, threshold, color_flag);
    return output_image;
}
Mat colored( Point seed, float threshold, char color_flag){
     Mat float_image,output_image;
    resize(src, src, Size(400, 400));
    // Convert image to float for better precision
    src.convertTo(float_image, CV_32FC3);
    output_image = Mat::zeros(src.size(), CV_8UC3);
     region_growing_segmentation(float_image,output_image, seed, threshold, color_flag);
    return output_image;
}

// calculate the distance between 2 points
double euclideanDistance(const vector<double> &p1, const vector<double> &p2)
{
    if (p1.size() != p2.size())
    {
        throw invalid_argument("Point dimensions do not match");
    }
    double sum = 0.0;
    for (size_t i = 0; i < p1.size(); ++i)
    {
        double diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

// compares every pair of points from the two clusters and determines the distance between them using the distance function
double clustersDistance(const vector<vector<double>> &cluster1, const vector<vector<double>> &cluster2){
    double max_dist = 0.0;
    for (const auto &point1 : cluster1)
    {
        for (const auto &point2 : cluster2)
        {
            double dist =
                    euclideanDistance(point1, point2);
            if (dist > max_dist)
            {
                max_dist = dist;
            }
        }
    }
    return max_dist;
}

// create the first cluster points
vector<vector<vector<double>>> initialClusters(Mat PixelsMatrix){
    vector<vector<vector<double>>> clusters;
    vector<double> allComparingResult;
    int initial_k = 20;
    vector<vector<vector<double>>>
    groups(initial_k);
    int d = static_cast<int>(256 / initial_k);
    for (int i = 0; i < PixelsMatrix.rows; i++)
    {
    vector<double> matrix_value_point =
            PixelsMatrix.row(i);
    for (int j = 0; j < initial_k; j++)
    {
    double k = j * d;
    vector<double> color_value_point ={k, k, k};
    double result =euclideanDistance(matrix_value_point,
                               color_value_point);
    allComparingResult.push_back(result);
    }
    auto it =std::min_element(allComparingResult.begin(),allComparingResult.end());
    int index =std::distance(allComparingResult.begin(), it);

    groups[index].push_back(matrix_value_point);
    allComparingResult.clear();
    }
    for (const auto &group : groups)
    {
    if (!group.empty())
    {
    vector<vector<double>> point_group;
    for (const auto &point : group)
    {
    point_group.push_back(point);
    }
    clusters.push_back(point_group);
    }
    }
    return clusters;
}

// get the min distance and merge the clusters with the smallest distance
void mergeCluster(int clusters_num, Mat &pixels, vector<int> &labels, map<int, vector<double>> &centers,map<vector<double>, int> &cluster_map){
    // Initially, assign each point to a distinct cluster
    vector<vector<vector<double>>> clusters_list = initialClusters(pixels);
    while (clusters_list.size() > clusters_num)
    {
        // Find the closest (most similar) pair of clusters
        vector<vector<double>> cluster1,cluster2;
        // DBL_MAX is a constant defined in the <cfloat> header file that represents the maximum finite value of type double.
        double min_distance = DBL_MAX;
        for (unsigned long long i = 0; i <clusters_list.size(); ++i)
        {
            for (unsigned long long j = 0; j < i; ++j)
            {
                double distance =clustersDistance(clusters_list[i],clusters_list[j]);
                if (distance < min_distance)
                {
                    min_distance = distance;
                    cluster1 =clusters_list[i];
                    cluster2 =clusters_list[j];
                }
            }
        }
        // Remove the two clusters from the clusters list

        clusters_list.erase(std::remove(clusters_list.begin(), clusters_list.end(), cluster1),clusters_list.end());

        clusters_list.erase(std::remove(clusters_list.begin(), clusters_list.end(), cluster2),clusters_list.end());
        // Merge the two clusters
        vector<vector<double>> merged_cluster =cluster1;

        merged_cluster.insert(merged_cluster.end(),cluster2.begin(), cluster2.end());
        // Add the merged cluster to the clusters list

        clusters_list.push_back(merged_cluster);
    }
    // Assign cluster number to each point
    cluster_map.clear();
    for (unsigned long long i = 0; i < clusters_list.size();++i)
    {
        for (unsigned long long j = 0; j <clusters_list[i].size(); ++j)
        {
            cluster_map[clusters_list[i][j]] =i;
        }
    }
    // Compute cluster centers
    centers.clear();
    for (unsigned long long i = 0; i < clusters_list.size();++i)
    {
        Mat cluster_mat(clusters_list[i].size(),clusters_list[i][0].size(), CV_64FC1);
        for (unsigned long long j = 0; j <clusters_list[i].size(); ++j)
        {
            for (unsigned long long k = 0; k <clusters_list[i][j].size(); ++k)
            {
                cluster_mat.at<double>(j, k) =clusters_list[i][j][k];
            }
        }
        Mat center_mat;
        reduce(cluster_mat, center_mat, 0,REDUCE_AVG);
        vector<double> center;
        for (int j = 0; j < center_mat.cols; ++j)
        {

            center.push_back(center_mat.at<double>(0, j));
        }
        centers[i] = center;
    }
    // Assign cluster center to each point
    labels.clear();
    for (int i = 0; i < pixels.rows; ++i)
    {
        vector<double> pixel = pixels.row(i);
        int cluster_num = cluster_map[pixel];
        labels.push_back(cluster_num);
    }
}

// Function to predict the cluster number of a given point
int predict_cluster(map<vector<double>, int>&cluster_map, vector<double> &point){
// Find cluster number of point
return cluster_map[point];
}
// Function to predict the center of the cluster that a given point belongs to
    vector<double> predict_center(map<int,vector<double>> &centers, map<vector<double>,int> &cluster_map, vector<double> &point)
{
// Find center of the cluster that point belongs to
int point_cluster_num =predict_cluster(cluster_map, point);
vector<double> center =centers[point_cluster_num];
return center;
}

pair<Mat, Mat> imagePreperation(Mat&image){
    Mat resized_image;
    Mat pixels;
    // Resize the image to 300x300 pixels
    resize(image, resized_image, Size(300,300));
    // Convert the input image to a onedimensional array of pixels
    pixels = resized_image.reshape(1,resized_image.rows * resized_image.cols);
    return {pixels, resized_image};
}

// the function that segment the image
Mat agglomerativeClustering(Mat &pixels, Mat &resized_image, int clusters_num){
    // Perform agglomerative clustering to segment the image into k clusters
    vector<int> labels;
    map<int, vector<double>> centers;
    map<vector<double>, int> cluster_map;
    mergeCluster(clusters_num, pixels, labels, centers,cluster_map);
    // Create a new image with each pixel assigned to its corresponding cluster center
    Mat segmented_image(resized_image.size(),resized_image.type());
    for (int i = 0; i < resized_image.rows;++i)
    {
        for (int j = 0; j < resized_image.cols;++j)
        {
            Vec3b pixel =resized_image.at<Vec3b>(i, j);
            vector<double> point ={(double)pixel[0], (double)pixel[1],(double)pixel[2]};
            vector<double> center =predict_center(centers, cluster_map, point);
            Vec3b new_pixel(center[0],center[1], center[2]);
            segmented_image.at<Vec3b>(i, j) =new_pixel;
        }
    }
    return segmented_image;
}
