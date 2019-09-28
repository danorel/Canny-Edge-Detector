//
// Created by Dan Orel on 2019-09-27.
//
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iomanip>
#include <cmath>

#include "gaussian_filter.h"
#include "sobel_operator.h"

using namespace cv;
#ifndef CANNY_EDGE_DETECTOR_HANDS_METHODS_H
#define CANNY_EDGE_DETECTOR_HANDS_METHODS_H
class CannyEdgeDetector{
public:
    CannyEdgeDetector(const Mat&);
    Mat start();
    void setupGaussianKernel(int, double);
    void setupThresholdParameters(int, int);
    ~CannyEdgeDetector();
private:
    Mat NonMaximaSuppresion(const Mat &, const Mat &);
    Mat ThresholdDropper(const Mat &, int, int);

private:
    Mat Image;

private:
    GaussianBlurManager Gaussian = GaussianBlurManager(Mat());
    int gaussian_kernel_size     = 0;
    double gaussian_sigma        = 0.;

private:
    SobelOperator Sobel = SobelOperator(Mat());

private:
    int threshold_minimum = 0,
        threshold_maximum = 0;
};
#endif //CANNY_EDGE_DETECTOR_HANDS_METHODS_H
