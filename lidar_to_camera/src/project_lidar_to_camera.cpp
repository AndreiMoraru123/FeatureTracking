//
// Created by Andrei on 03-Nov-22.
//

#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "D:\CameraVision\TTC-camera\src\dataStructure.h"
#include "D:\CameraVision\TTC-camera\src\structIO.hpp"
#include "D:\CameraVision\TTC-camera\src\structIO.cpp"

using namespace std;

void loadCalibrationData(cv::Mat &P_rect_00, cv::Mat &R_rect_00, cv::Mat &RT)
{
//        // load 3x4 projection matrix after rectification
//        cv::FileStorage fs(R"(D:\CameraVision\TTC-camera\dat\Camera_0\projMatr.dat)", cv::FileStorage::READ);
//        fs["P_rect_0"] >> P_rect_0;
//        fs.release();
//
//        // load 3x3 rectifying rotation to make image planes co-planar
//        fs.open(R"(D:\CameraVision\TTC-camera\dat\Camera_0\R_rect_00.dat)", cv::FileStorage::READ);
//        fs["R_rect_00"] >> R_rect_00;
//        fs.release();
//
//        // load 3x4 projection matrix after rectification
//        fs.open(R"(D:\CameraVision\TTC-camera\dat\Camera_0\RT.dat)", cv::FileStorage::READ);
//        fs["RT"] >> RT;
//        fs.release();

      RT.at<double>(0,0) = 7.533745e-03; RT.at<double>(0,1) = -9.999714e-01; RT.at<double>(0,2) = -6.166020e-04; RT.at<double>(0,3) = -4.069766e-03;
      RT.at<double>(1,0) = 1.480249e-02; RT.at<double>(1,1) = 7.280733e-04; RT.at<double>(1,2) = -9.998902e-01; RT.at<double>(1,3) = -7.631618e-02;
      RT.at<double>(2,0) = 9.998621e-01; RT.at<double>(2,1) = 7.523790e-03; RT.at<double>(2,2) = 1.480755e-02; RT.at<double>(2,3) = -2.717806e-01;
      RT.at<double>(3,0) = 0.0; RT.at<double>(3,1) = 0.0; RT.at<double>(3,2) = 0.0; RT.at<double>(3,3) = 1.0;

      R_rect_00.at<double>(0,0) = 9.999239e-01; R_rect_00.at<double>(0,1) = 9.837760e-03; R_rect_00.at<double>(0,2) = -7.445048e-03; R_rect_00.at<double>(0,3) = 0.0;
      R_rect_00.at<double>(1,0) = -9.869795e-03; R_rect_00.at<double>(1,1) = 9.999421e-01; R_rect_00.at<double>(1,2) = -4.278459e-03; R_rect_00.at<double>(1,3) = 0.0;
      R_rect_00.at<double>(2,0) = 7.402527e-03; R_rect_00.at<double>(2,1) = 4.351614e-03; R_rect_00.at<double>(2,2) = 9.999631e-01; R_rect_00.at<double>(2,3) = 0.0;
      R_rect_00.at<double>(3,0) = 0; R_rect_00.at<double>(3,1) = 0; R_rect_00.at<double>(3,2) = 0; R_rect_00.at<double>(3,3) = 1;

      P_rect_00.at<double>(0,0) = 7.215377e+02; P_rect_00.at<double>(0,1) = 0.000000e+00; P_rect_00.at<double>(0,2) = 6.095593e+02; P_rect_00.at<double>(0,3) = 0.000000e+00;
      P_rect_00.at<double>(1,0) = 0.000000e+00; P_rect_00.at<double>(1,1) = 7.215377e+02; P_rect_00.at<double>(1,2) = 1.728540e+02; P_rect_00.at<double>(1,3) = 0.000000e+00;
      P_rect_00.at<double>(2,0) = 0.000000e+00; P_rect_00.at<double>(2,1) = 0.000000e+00; P_rect_00.at<double>(2,2) = 1.000000e+00; P_rect_00.at<double>(2,3) = 0.000000e+00;
}

void projectLidarToCamera2()
{
        cv::Mat img = cv::imread(R"(D:\CameraVision\TTC-camera\dat\Camera_0\image_0\0000000000.png)");

        std::vector<LidarPoint> lidarPoints;
        readLidarPts(R"(D:/CameraVision/lidar_to_camera/dat/C51_LidarPts_0000.dat)", lidarPoints);

        cv::Mat P_rect_00(3, 4, cv::DataType<double>::type); // 3x4 projection matrix after rectification
        cv::Mat R_rect_00(4, 4, cv::DataType<double>::type); // 3x3 rectifying rotation to make image planes co-planar
        cv::Mat RT(4, 4, cv::DataType<double>::type); // rotation matrix and translation vector
        loadCalibrationData(P_rect_00, R_rect_00, RT);

        cv::Mat visImg = img.clone();
        cv::Mat overlay = visImg.clone();

        cv::Mat X(4, 1, cv::DataType<double>::type);
        cv::Mat Y(3, 1, cv::DataType<double>::type);

        for (auto it = lidarPoints.begin(); it != lidarPoints.end(); ++it)
        {
                X.at<double>(0, 0) = it->x;
                X.at<double>(1, 0) = it->y;
                X.at<double>(2, 0) = it->z;
                X.at<double>(3, 0) = 1;

                Y = P_rect_00 * R_rect_00 * RT * X;
                cv::Point pt;
                pt.x = Y.at<double>(0, 0) / Y.at<double>(0, 2);
                pt.y = Y.at<double>(1, 0) / Y.at<double>(0, 2);

                cv::circle(overlay, pt, 5, cv::Scalar(0, 255, 0), -1);


        }

//        cv::addWeighted(visImg, 1.0, overlay, 0.3, 0, overlay);
        string windowName = "LiDAR data on image overlay";
        cv::namedWindow(windowName, 1);
        cv::imshow(windowName, overlay);
        cv::waitKey(0); // wait for key to be pressed
}

int main()
{
        projectLidarToCamera2();
}