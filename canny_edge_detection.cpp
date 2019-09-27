//
// Created by Dan Orel on 2019-09-27.
//
#include "canny_edge_detection.h"
#include "gaussian_filter.h"
#include "sobel_operator.h"

CannyEdgeDetector::CannyEdgeDetector(const Mat &Image) {
    this->Image = Image;
    this->kernel_size = 5;
}

Mat CannyEdgeDetector::start() {
    GaussianBlurManger(this->Image, this->kernel_size, )
    return Mat();
}

void CannyEdgeDetector::setupGaussianKernel(short kernel_size) {
    this->kernel_size = kernel_size;
}

CannyEdgeDetector::~CannyEdgeDetector() {

}
