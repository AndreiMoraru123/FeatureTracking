//
//  structIO.hpp
//  OpenCVTest
//
//  Created by Prof. Dr. Andreas Haja on 24.04.19.
//  Copyright © 2019 Andreas Haja. All rights reserved.
//

#ifndef structIO_hpp
#define structIO_hpp

#include <stdio.h>
#include "dataStructure.h"

void writeLidarPts(std::vector<LidarPoint> &input, const char* fileName);
void readLidarPts(const char* fileName, std::vector<LidarPoint> &output);

void writeKeypoints(std::vector<cv::KeyPoint> &input, const char* fileName);
void readKeypoints(const char* fileName, std::vector<cv::KeyPoint> &output);

void writeKptMatches(std::vector<cv::DMatch> &input, const char* fileName);
void readKptMatches(const char* fileName, std::vector<cv::DMatch> &output);

void writeBoundingBoxes(std::vector<BoundingBox> &input, const char* fileName);
void readBoundingBoxes(const char* fileName, std::vector<BoundingBox> &output);

void writeDescriptors(cv::Mat &input, const char* fileName);
void readDescriptors(const char* fileName, cv::Mat &output);


template<typename T> void write_pod(std::ofstream& out, T& t);
template<typename T> void read_pod(std::ifstream& in, T& t);
template<typename T> void read_pod_vector(std::ifstream& in, std::vector<T>& vect);
template<typename T> void write_pod_vector(std::ofstream& out, std::vector<T>& vect);

#endif /* structIO_hpp */