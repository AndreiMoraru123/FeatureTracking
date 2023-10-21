//
// Created by Andrei on 24-Oct-22.
//

#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace std;

void detectKeypoints1()
{
    cv::Mat imgGray;
    cv::Mat img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1.png)");
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // Shi-Tomasi detector
    int blockSize = 4;     // size of an average block for computing a derivative covariation matrix over each pixel neighborhood
    double maxOverlap = 0.0; // max. permissible overlap between two features in %
    double minDistance = (1.0 - maxOverlap) * blockSize; // min. distance between features - computed as desired overlap
    int maxCorners = img.rows * img.cols / std::max(1.0, minDistance); // max. num. of keypoints
    double qualityLevel = 0.01; // minimal accepted quality of image corners
    double k = 0.04; // Harris parameter (see equation for details)
    bool useHarrisDetector = false;

    vector<cv::KeyPoint> kptsShiTomasi;
    vector<cv::Point2f> corners;

    double t = (double)cv::getTickCount();
    cv::goodFeaturesToTrack(imgGray, corners, maxCorners, qualityLevel, minDistance, cv::Mat(), blockSize, useHarrisDetector, k);
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
    cout << "Shi-Tomasi with n=" << corners.size() << " keypoints in " << 1000 * t / 1.0 << " ms" << endl;

    // visualize results
    for (auto it = corners.begin(); it != corners.end(); ++it)
    {
        // draw a circle at each corner location
//        cv::circle(img, *it, 4, cv::Scalar(0, 255, 0), 1);
        cv::KeyPoint newKeyPoint;
        newKeyPoint.pt = cv::Point2f((*it).x, (*it).y);
        newKeyPoint.size = 2 * blockSize;
        kptsShiTomasi.push_back(newKeyPoint);
    }


    string windowName = "Shi-Tomasi Results";
    cv::drawKeypoints(img, kptsShiTomasi, img, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow(windowName, 1);
    cv::imshow(windowName, img);
    cv::waitKey(0);
}

void describeKeypoints1(){

    cv::Mat imgGray;
    cv::Mat img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1.png)");
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    cv::Ptr<cv::FeatureDetector> detector = cv::SIFT::create();
    vector<cv::KeyPoint> kpts;
    detector->detect(imgGray, kpts);

    cv::Ptr<cv::DescriptorExtractor> extractor = cv::SIFT::create();
    cv::Mat descriptors;
    extractor->compute(imgGray, kpts, descriptors);

    cout << "keypoints: " << kpts.size() << endl;
    cout << "descriptor matrix size: " << descriptors.rows << " by " << descriptors.cols << endl;

    string windowName = "ORB Results";
    cv::drawKeypoints(img, kpts, img, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::namedWindow(windowName, 1);
    cv::imshow(windowName, img);
    cv::waitKey(0);
}

int main()
{
//    detectKeypoints1();
    describeKeypoints1();
    return 0;
}