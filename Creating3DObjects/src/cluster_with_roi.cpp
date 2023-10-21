//
// Created by Andrei on 04-Nov-22.
//

#include "../../TTC-camera/src/dataStructure.h"
#include "../../TTC-camera/src/structIO.cpp"
#include "../../TTC-camera/src/structIO.hpp"
#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void loadCalibrationData(cv::Mat &P_rect_00, cv::Mat &R_rect_00, cv::Mat &RT)
{
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

void showLidarTopview(std::vector<LidarPoint> &lidarPoints, cv::Size worldSize, cv::Size imageSize, bool bWait=true)
{
  // create topview image
  cv::Mat topviewImg(imageSize, CV_8UC3, cv::Scalar(0, 0, 0));

  // plot Lidar points into image
  double topviewScale = static_cast<double>(imageSize.height) / static_cast<double>(worldSize.height);
  for (auto it = lidarPoints.begin(); it != lidarPoints.end(); ++it)
  {
    double xw = (*it).x; // world position in m with x facing forward from sensor
    double yw = (*it).y; // world position in m with y facing left from sensor
    int y = (-xw * topviewScale) + static_cast<double>(imageSize.height);
    int x = (-yw * topviewScale) + static_cast<double>(imageSize.width) / 2.0;
    cv::circle(topviewImg, cv::Point(x, y), 5, cv::Scalar(0, 255, 0), -1);
  }

  // plot distance markers
  int lineSpacing = 8;
  float lineLength = 1.0;
  for (size_t i = 0; i < imageSize.height / lineSpacing; ++i)
  {
    int y = static_cast<int>(static_cast<double>(i) * static_cast<double>(lineSpacing));
    cv::line(topviewImg, cv::Point(0, y), cv::Point(2, y), cv::Scalar(255, 0, 0), lineLength);
    cv::line(topviewImg, cv::Point(imageSize.width - 2, y), cv::Point(imageSize.width, y), cv::Scalar(255, 0, 0), lineLength);
  }

  // display image
  string windowName = "LiDAR data on top view image";
  cv::namedWindow(windowName, 2);
  cv::imshow(windowName, topviewImg);
  if (bWait)
  {
    cv::waitKey(0); // wait for key to be pressed
  }
}

void clustterLidarWithROI(std::vector<BoundingBox> &boundingBoxes, std::vector<LidarPoint> &lidarPoints)
{
  // store calibration data
        cv::Mat P_rect_00(3, 4, cv::DataType<double>::type);
        cv::Mat R_rect_00(4, 4, cv::DataType<double>::type);
        cv::Mat RT(4, 4, cv::DataType<double>::type);
        loadCalibrationData(P_rect_00, R_rect_00, RT);

        cv::Mat X(4, 1, cv::DataType<double>::type);
        cv::Mat Y(3, 1, cv::DataType<double>::type);

        for (auto it1 =lidarPoints.begin(); it1 != lidarPoints.end(); ++it1)
        {
            X.at<double>(0,0) = (*it1).x;
            X.at<double>(1,0) = (*it1).y;
            X.at<double>(2,0) = (*it1).z;
            X.at<double>(3,0) = 1;

            Y = P_rect_00 * R_rect_00 * RT * X;

//            (*it1).x = Y.at<double>(0,0) / Y.at<double>(0,2);
//            (*it1).y = Y.at<double>(1,0) / Y.at<double>(0,2);
//            (*it1).z = Y.at<double>(2,0) / Y.at<double>(0,2);

            cv::Point pt;
            pt.x = Y.at<double>(0,0) / Y.at<double>(0,2);
            pt.y = Y.at<double>(1,0) / Y.at<double>(0,2);

            double shrinkFactor = 0.15;
            vector<vector<BoundingBox>> enclosingBoxes;
            for (auto it2 = boundingBoxes.begin(); it2 != boundingBoxes.end(); ++it2)
            {
              // shrink current bounding box slightly to avoid having too many outlier points around the edges
              cv::Rect smallerBox;
              smallerBox.x = (*it2).roi.x + shrinkFactor * (*it2).roi.width / 2.0;
              smallerBox.y = (*it2).roi.y + shrinkFactor * (*it2).roi.height / 2.0;
              smallerBox.width = (*it2).roi.width * (1 - shrinkFactor);
              smallerBox.height = (*it2).roi.height * (1 - shrinkFactor);

              // check wether point is within current bounding box
              if (smallerBox.contains(pt))
              {
                it2->lidarPoints.push_back(*it1);
                lidarPoints.erase(it1);
                it1--;
                break;
              }
            } // eof loop over all bounding boxes

            // TODO - check wether point has been enclosed by one or by multiple boxes.
            // Accordingly, add Lidar point to bounding box and remove it from lidarPoints

            if (enclosingBoxes.size() == 1)
            { // add point to bounding box
              enclosingBoxes[0][0].lidarPoints.push_back(*it1);
            }
            else if (enclosingBoxes.size() > 1)
            { // add point to all bounding boxes
              for (auto it3 = enclosingBoxes.begin(); it3 != enclosingBoxes.end(); ++it3)
              {
                (*it3)[0].lidarPoints.push_back(*it1);
              }
            }

        }
}

int main()
{
  cv::Mat img = cv::imread(R"(D:\CameraVision\TTC-camera\dat\Camera_0\image_0\0000000000.png)");

  std::vector<LidarPoint> lidarPoints;
  readLidarPts(R"(D:\CameraVisio\Creating3DObjects\dat\C53A3_currLidarPts.dat)", lidarPoints);
//  showLidarTopview(lidarPoints, cv::Size(10.0, 25.0), cv::Size(1000, 2000), true);
  std::vector<BoundingBox> boundingBoxes;
  readBoundingBoxes(R"(D:\CameraVision\Creating3DObjects\dat\C53A3_currBoundingBoxes.dat)", boundingBoxes);
}