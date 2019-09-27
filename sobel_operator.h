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
#ifndef CANNY_EDGE_DETECTOR_SOBOL_OPERATOR_H
#define CANNY_EDGE_DETECTOR_SOBOL_OPERATOR_H
Mat SobelOperator(const Mat&);
double** Gy();
double** Gx();
#endif //CANNY_EDGE_DETECTOR_SOBOL_OPERATOR_H
