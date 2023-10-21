//
// Created by Andrei on 16-Oct-22.
//

#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>

#include "dataStructure.h"
#include "structIO.hpp"

using namespace std;

void computeTTCLidar(std::vector<LidarPoint> &LidarPointsPrev,
                     std::vector<LidarPoint> &LidarPointsCurr, double &TTC)
{
    // auxiliary variables
    double dT = 0.1; // time between two measurements in seconds
    double laneWidth = 4.0; // assumed width of the ego lane

    // find closest distance to Lidar points within ego lane
    double minXPrev = 1e9, minXCurr = 1e9;
    for (auto it = LidarPointsPrev.begin(); it != LidarPointsPrev.end(); ++it)
    {
        if (abs(it->y) <= laneWidth / 2.0)
        { // 3D point within ego lane?
            minXPrev = minXPrev > it->x ? it->x : minXPrev;
        }
    }

    for (auto it = LidarPointsCurr.begin(); it != LidarPointsCurr.end(); ++it)
    {
        if (abs(it->y) <= laneWidth / 2.0)
        { // 3D point within ego lane?
            minXCurr = minXCurr > it->x ? it->x : minXCurr;
        }
    }

    TTC = minXCurr * dT / (minXPrev - minXCurr);
}

int main()
{
    std::vector<LidarPoint> currLidarPts, prevLidarPts;
    readLidarPts(R"(D:\CameraVision\TTC-lidar\dat\C22A5_currLidarPts.dat)", currLidarPts);
//    readLidarPts(R"(D:/CameraVision/lidar_to_camera/dat/C51_LidarPts_0000.dat)", currLidarPts);
    readLidarPts(R"(D:\CameraVision\TTC-lidar\dat\C22A5_prevLidarPts.dat)", prevLidarPts);

    double ttc;
    computeTTCLidar(prevLidarPts, currLidarPts, ttc);
    cout << "ttc = " << ttc << " s" << endl;
}