//
// Created by Andrei on 23-Oct-22.
//

#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

cv::Mat gaussianSmoothing1() {
    cv::Mat img;
    img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1gray.png)",
                     cv::IMREAD_GRAYSCALE);

    cv::Mat img_filtered;
    cv::GaussianBlur(img, img_filtered, cv::Size(5, 5), 2.0, 2.0);

    return img_filtered;
}

void magSobel(){
    cv::Mat img = gaussianSmoothing1();

    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;

    cv::Sobel(img, grad_x, CV_32F, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::Sobel(img, grad_y, CV_32F, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT);

    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);

//    cv::Mat grad;
//    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    // magnitude
    cv::Mat magnitude;
    cv::magnitude(grad_x, grad_y, magnitude);

//    cv::Mat magnitude = img.clone();
//        for (int i = 0; i < img.rows; i++) {
//            for (int j = 0; j < img.cols; j++) {
//                magnitude.at<uchar>(i, j) = sqrt(pow(grad_x.at<uchar>(i, j), 2) + pow(grad_y.at<uchar>(i, j), 2));
//            }
//        }

    string windowName = "First image";
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::imshow(windowName, magnitude);
    cv::waitKey(0); // wait for a keystroke in the window before continuing
}

void magnitudeSobel()
{
    // load image from file
    cv::Mat img;
    img = cv::imread(R"(D:\CameraVision\IntensityGradientAndFiltering\gradient_filtering\images\img1.png)");

    // convert image to grayscale
    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    // apply smoothing using the GaussianBlur() function from the OpenCV
    // ToDo : Add your code here

    cv::Mat blurred = imgGray.clone();
    cv::GaussianBlur(img, blurred, cv::Size(5,5), 2.0, 2.0);

    float sobel_x[9] = {-1, 0, +1, -2, 0, +2, -1, 0, +1};
    cv::Mat kernel_x = cv::Mat(3, 3, CV_32F, sobel_x);

    float sobel_y[9] = {-1, -2, -1, 0, 0, 0, +1, +2, +1};
    cv::Mat kernel_y = cv::Mat(3, 3, CV_32F, sobel_y);

    // create filter kernels using the cv::Mat datatype both for x and y
    // ToDo : Add your code here

    cv::Mat result_x, result_y;
    cv::filter2D(blurred, result_x, -1, kernel_x, cv::Point(-1,-1),0, cv::BORDER_DEFAULT);

    cv::filter2D(blurred, result_y, -1, kernel_y, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
    // apply filter using the OpenCv function filter2D()
    // ToDo : Add your code here


    // compute magnitude image based on the equation presented in the lesson
    // TODO : Add your code here
    cv::Mat magnitude = imgGray.clone();
    for (int r = 0; r < magnitude.rows; r++)
    {
        for (int c = 0; c < magnitude.cols; c++)
        {
            magnitude.at<unsigned char>(r, c) = sqrt(pow(result_x.at<unsigned char>(r, c), 2) +
                                                     pow(result_y.at<unsigned char>(r, c), 2));
        }
    }

    // show result
    string windowName = "Gaussian Blurring";
    cv::namedWindow(windowName, 1); // create window
    cv::imshow(windowName, magnitude);
    cv::waitKey(0); // wait for keyboard input before continuing
}


int main() {
    magnitudeSobel();
    return 0;
}