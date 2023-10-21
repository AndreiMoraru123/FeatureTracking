//
// Created by Andrei on 24-Oct-22.
//

#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<opencv2/features2d.hpp>

using namespace std;

void cornernessHarris()
{

    cv::Mat img;
    img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1.png)");
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    int blocksize = 2;
    int apertureSize = 3;
    int minResponse = 100;
    double k = 0.04;

    // Detect Harris corners and normalize output
    cv::Mat dst, dst_norm, dst_norm_scaled;
    dst = cv::Mat::zeros(img.size(), CV_32FC1);
    cv::cornerHarris(img, dst, blocksize, apertureSize, k, cv::BORDER_DEFAULT);
    cv::normalize(dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
    cv::convertScaleAbs(dst_norm, dst_norm_scaled);

    // Look for prominent corners and instantiate keypoints
    vector<cv::KeyPoint> keypoints;
    for (size_t j = 0; j < dst_norm.rows; j++)
    {
        for (size_t i = 0; i < dst_norm.cols; i++)
        {
            if ((int)dst_norm.at<float>(j, i) > minResponse)
            {
                cv::KeyPoint newKeyPoint;
                newKeyPoint.pt = cv::Point2f(i, j);
                newKeyPoint.size = 2 * apertureSize;
                newKeyPoint.response = dst_norm.at<float>(j, i);
                // Perform non-maximum suppression (NMS) in local neighbourhood around new key point
                bool bOverlap = false;
                for (auto it = keypoints.begin(); it != keypoints.end(); ++it)
                {
                    double kptOverlap = cv::KeyPoint::overlap(newKeyPoint, *it);
                    if (kptOverlap > 0.0)
                    {
                        bOverlap = true;
                        if (newKeyPoint.response > (*it).response)
                        {
                            *it = newKeyPoint; // replace old key point with new one
                            break; // quit loop over keypoints
                        }
                    }
                }
                if (!bOverlap)
                {                                     // only add new key point if no overlap has been found in previous NMS
                    keypoints.push_back(newKeyPoint); // store new keypoint in dynamic list
                }
            } // eof only if response is larger than minResponse
        }     // eof loop over cols
    }         // eof loop over rows

    // visualize keypoints
    string windowName = "Harris Corner Detector Response Matrix";
    cv::namedWindow(windowName, 1);
    cv::Mat visImage = dst_norm_scaled.clone();
    cv::drawKeypoints(dst_norm_scaled, keypoints, visImage, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow(windowName, visImage);
    cv::waitKey(0); // wait for a keystroke in the window before continuing
}

int main()
{
    cornernessHarris();
    return 0;
}