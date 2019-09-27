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
#ifndef CANNY_EDGE_DETECTOR_GAUSSIAN_FILTER_H
#define CANNY_EDGE_DETECTOR_GAUSSIAN_FILTER_H
Mat GaussianBlur(const Mat& Image, int kernel_size, double sigma);
double** GaussianKernel(int kernel_size, double sigma);
double KernelFunction(double x, double y, double sigma);
#endif //CANNY_EDGE_DETECTOR_GAUSSIAN_FILTER_H
