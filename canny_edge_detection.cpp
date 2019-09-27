//
// Created by Dan Orel on 2019-09-27.
//
#include "canny_edge_detection.h"

CannyEdgeDetector::CannyEdgeDetector(const Mat &Image){
    this->Image                = Image;
    this->gaussian_kernel_size = 3;
    this->gaussian_sigma       = 1.;
}

Mat CannyEdgeDetector::start() {
    // Process input image with Gaussian Filter
    this->Gaussian = GaussianBlurManager(this->Image);
    this->Gaussian.setupKernel(this->gaussian_kernel_size, this->gaussian_sigma);
    Mat ImageGaussianFiltered = this->Gaussian.process();
    // Process input image with Sobel Operator
    this->Sobel    = SobelOperator(ImageGaussianFiltered);
    Mat ImageSobelFiltered    = this->Sobel.process();
    return ImageSobelFiltered;
}

void CannyEdgeDetector::setupGaussianKernel(int kernel_size, double sigma) {
    this->gaussian_kernel_size = kernel_size;
    this->gaussian_sigma       = sigma;
}

CannyEdgeDetector::~CannyEdgeDetector() {

}
