//
// Created by Andrei on 16-Oct-22.
//

#ifndef CAMERAVISION_DATASTRUCTURE_H
#define CAMERAVISION_DATASTRUCTURE_H

#include<vector>
#include<opencv2/core.hpp>

struct LidarPoint{
    double x, y, z; // world coordinates in m
    double r; // reflectivity
};

struct BoundingBox {
  int boxID; // unique identifier for this bounding box
  int trackID; // unique identifier for the track to which this bounding box belongs

  cv::Rect roi; // 2D region-of-interest in image coordinates
  int classID; // ID based on class file provided to YOLO framework
  double confidence; // classification trust

  std::vector<LidarPoint> lidarPoints; // Lidar 3D points which project into 2D image roi
  std::vector<cv::KeyPoint> keypoints; // keypoints enclosed by 2D roi
  std::vector<cv::DMatch> kptMatches; // keypoint matches enclosed by 2D roi
};

#endif //CAMERAVISION_DATASTRUCTURE_H
