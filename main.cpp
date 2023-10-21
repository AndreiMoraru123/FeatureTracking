#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/features2d/features2d.hpp>

int main() {
    cv::Mat image;
    cv::VideoCapture capture;
    capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    capture.open(0);

    while(true) {
        capture >> image;
        cv::imshow("test", image);

        int c = cv::waitKey(10);
        if (c == 27) break;
    }

//    enum class DetectorType {
//        SHITOMASI,
//        HARRIS,
//        FAST,
//        BRISK,
//        ORB,
//        AKAZE,
//        SIFT
//    };

    return 0;
}
