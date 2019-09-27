//
// Created by Dan Orel on 2019-09-27.
//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iomanip>
#include <cmath>

using namespace cv;
#ifndef CANNY_EDGE_DETECTOR_HANDS_METHODS_H
#define CANNY_EDGE_DETECTOR_HANDS_METHODS_H
class CannyEdgeDetector{
public:
    CannyEdgeDetector(const Mat&);
    Mat start();
    void setupGaussianKernel(short);
    ~CannyEdgeDetector();
private:
    Mat Image;
    short kernel_size;
};
#endif //CANNY_EDGE_DETECTOR_HANDS_METHODS_H
