//
// Created by Andrei on 23-Oct-22.
//
#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void gradientSobel()
{
    cv::Mat img;
    img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1gray.png)", cv::IMREAD_GRAYSCALE);

    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    cv::Sobel(img, grad_x, CV_16S, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(img, grad_y, CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);

    cv::Mat grad;
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    string windowName = "First image";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, grad);
    cv::waitKey(0); // wait for a keystroke in the window before continuing
}


void manualSobel()
{
    cv::Mat img;
    img= cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1.png)");

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    float sobel_x[9] = {-1, 0, 1,
                        -2, 0, 2,
                        -1, 0, 1};
    cv::Mat result_x;
    cv::filter2D(imgGray, result_x, -1, cv::Mat(3, 3, CV_32F, sobel_x), cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    float sobel_y[9] = {-1, -2, -1,
                        0, 0, 0,
                        1, 2, 1};

    cv::Mat result_y;
    cv::filter2D(imgGray, result_y, -1, cv::Mat(3, 3, CV_32F, sobel_y), cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    cv::Mat result;
    cv::addWeighted(result_x, 0, result_y, 1, 0, result);

    string windowName = "First image";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, result);
    cv::waitKey(0); // wait for a keystroke in the window before continuing
}

int main()
{
//    gradientSobel();
    manualSobel();
    return 0;
}