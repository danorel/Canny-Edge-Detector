//
// Created by Dan Orel on 2019-09-27.
//
#include "canny_edge_detection.h"

CannyEdgeDetector::CannyEdgeDetector(const Mat &Image){
    this->Image                = Image;
    this->gaussian_kernel_size = 3;
    this->gaussian_sigma       = 1.;
    this->threshold_minimum    = 20;
    this->threshold_maximum    = 60;
}

Mat CannyEdgeDetector::start() {
    Mat ImageCannyDetected(
            this->Image.rows,
            this->Image.cols,
            CV_8UC1
    );
    // Process input image with Gaussian Filter
    this->Gaussian = GaussianBlurManager(this->Image);
    this->Gaussian.setupKernel(this->gaussian_kernel_size, this->gaussian_sigma);
    Mat ImageGaussianFiltered = this->Gaussian.process();
    // Process input image with Sobel Operator, receiving the AngleMap
    this->Sobel    = SobelOperator(ImageGaussianFiltered);
    Mat ImageSobelFiltered    = this->Sobel.process();
    Mat AngleMap = this->Sobel.GetAngleMap();
    // Performing the Non-maxima image suppresion
    Mat ImageNonMaximaSuppressed = NonMaximaSuppresion(ImageSobelFiltered, AngleMap);
    // Performing Threshold dropping process
    Mat ImageThresholdDropped = ThresholdDropper(ImageNonMaximaSuppressed, this->threshold_minimum, this->threshold_maximum);
    // Assigning the received transformed Image to the result Image
    ImageCannyDetected = ImageThresholdDropped;
    return ImageCannyDetected;
}

void CannyEdgeDetector::setupThresholdParameters(int minimum, int maximum) {
    this->threshold_minimum = minimum;
    this->threshold_maximum = maximum;
}

void CannyEdgeDetector::setupGaussianKernel(int kernel_size, double sigma) {
    this->gaussian_kernel_size = kernel_size;
    this->gaussian_sigma       = sigma;
}

Mat CannyEdgeDetector::NonMaximaSuppresion(const Mat &Image, const Mat &AngleMap){
    Mat ImageNonMaximaSuppressed(
            Image.rows - 2,
            Image.cols - 2,
            CV_8UC1
    );
    for(int row = 1; row < Image.rows - 1; row++){
        for(int column = 1; column < Image.cols - 1; column++){
            float Tangent = AngleMap.at<float>(row, column);

            ImageNonMaximaSuppressed.at<uchar>(row - 1, column - 1) = Image.at<uchar>(row, column);

            if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
            {
                if ((Image.at<uchar>(row, column) < Image.at<uchar>(row, column + 1)) || (Image.at<uchar>(row, column) < Image.at<uchar>(row,column - 1)))
                    ImageNonMaximaSuppressed.at<uchar>(row - 1, column - 1) = 0;
            }
            //Vertical Edge
            if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
            {
                if ((Image.at<uchar>(row, column) < Image.at<uchar>(row + 1, column)) || (Image.at<uchar>(row, column) < Image.at<uchar>(row - 1, column)))
                    ImageNonMaximaSuppressed.at<uchar>(row-1, column - 1) = 0;
            }

            //-45 Degree Edge
            if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
            {
                if ((Image.at<uchar>(row, column) < Image.at<uchar>(row - 1,column + 1)) || (Image.at<uchar>(row, column) < Image.at<uchar>(row+1,column - 1)))
                    ImageNonMaximaSuppressed.at<uchar>(row - 1, column - 1) = 0;
            }

            //45 Degree Edge
            if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))
            {
                if ((Image.at<uchar>(row, column) < Image.at<uchar>(row + 1, column + 1)) || (Image.at<uchar>(row, column) < Image.at<uchar>(row - 1, column - 1)))
                    ImageNonMaximaSuppressed.at<uchar>(row - 1, column - 1) = 0;
            }
        }
    }
    return ImageNonMaximaSuppressed;
}

Mat CannyEdgeDetector::ThresholdDropper(const Mat &Image, int minimum, int maximum) {
    if(minimum > 255)
        minimum = 255;
    if(maximum > 255)
        maximum = 255;
    // Initializing step
    Mat ImageThresholdDropped (
            Image.rows,
            Image.cols,
            Image.type()
    );

    for (int row = 0; row < Image.rows; row++)
    {
        for (int column = 0; column < Image.cols; column++)
        {
            ImageThresholdDropped.at<uchar>(row, column) = Image.at<uchar>(row, column);
            if(ImageThresholdDropped.at<uchar>(row, column) > maximum)
                ImageThresholdDropped.at<uchar>(row, column) = 255;
            else if(ImageThresholdDropped.at<uchar>(row, column) < minimum)
                ImageThresholdDropped.at<uchar>(row, column) = 0;
            else {
                bool anyHigh = false;
                bool anyBetween = false;
                for (int x = row - 1; x < row + 2; x++)
                {
                    for (int y = column - 1; y < column + 2; y++)
                    {
                        if(x <= 0 || y <= 0 || ImageThresholdDropped.rows || y > ImageThresholdDropped.cols) //Out of bounds
                            continue;
                        else
                        {
                            if(ImageThresholdDropped.at<uchar>(x, y) > maximum)
                            {
                                ImageThresholdDropped.at<uchar>(row, column) = 255;
                                anyHigh = true;
                                break;
                            }
                            else if(ImageThresholdDropped.at<uchar>(x, y) <= maximum && ImageThresholdDropped.at<uchar>(x, y) >= minimum)
                                anyBetween = true;
                        }
                    }
                    if(anyHigh)
                        break;
                }
                if(!anyHigh && anyBetween)
                    for (int x = row - 2; x < row + 3; x++)
                    {
                        for (int y = column - 1; y < column + 3; y++)
                        {
                            if(x < 0 || y < 0 || x > ImageThresholdDropped.rows || y > ImageThresholdDropped.cols) //Out of bounds
                                continue;
                            else
                            {
                                if(ImageThresholdDropped.at<uchar>(x, y) > maximum)
                                {
                                    ImageThresholdDropped.at<uchar>(row, column) = 255;
                                    anyHigh = true;
                                    break;
                                }
                            }
                        }
                        if(anyHigh)
                            break;
                    }
                if(!anyHigh)
                    ImageThresholdDropped.at<uchar>(row, column) = 0;
            }
        }
    }
    return ImageThresholdDropped;
}

CannyEdgeDetector::~CannyEdgeDetector() {

}