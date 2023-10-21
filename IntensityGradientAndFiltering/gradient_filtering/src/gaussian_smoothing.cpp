//
// Created by Andrei on 23-Oct-22.
//
#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gaussianSmoothing1()
{
    cv::Mat img;
    img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1gray.png)", cv::IMREAD_GRAYSCALE);

    cv::Mat img_filtered;
    cv::GaussianBlur(img, img_filtered, cv::Size(7, 7), 3, 3);

//    float gauss_data[25] = {1, 4, 7, 4, 1,
//                            4, 16, 26, 16, 4,
//                            7, 26, 41, 26, 7,
//                            4, 16, 26, 16, 4,
//                            1, 4, 7, 4, 1};
//
//    cv::Mat kernel = cv::Mat(5, 5, CV_32F, gauss_data);
//
//    kernel = kernel / cv::sum(kernel)[0];
//
//    cv::Mat img_filtered;
//    cv::filter2D(img, img_filtered, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    string windowName = "First image";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, img_filtered);
    cv::waitKey(0); // wait for a keystroke in the window before continuing
}

int main()
{
    gaussianSmoothing1();
    return 0;
}