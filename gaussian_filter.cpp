//
// Created by Dan Orel on 2019-09-27.
//

#include "gaussian_filter.h"


GaussianBlurManager::GaussianBlurManager(const Mat &Image) {
    this->Image       = Image;
    this->kernel_size = 5;
    this->sigma       = 1.;
}

Mat GaussianBlurManager::process() {
    // Image parameters: width & height
    Mat BlurredImage = Image.clone();
    int columns      = Image.cols;
    int rows         = Image.rows;
    // Defining the kernel bounds
    int verticalBound   = (kernel_size - 1) / 2;
    int horizontalBound = (kernel_size - 1) / 2;
    // Initializing the Gaussian Kernel
    double **Kernel = GaussianKernel(kernel_size, sigma);
    // Blur the image
    for(int row = 0 + verticalBound; row < rows - verticalBound; row++){
        for(int column = 0 + horizontalBound; column < columns - horizontalBound; column++){
            float mean = 0.;
            for(int kernel_row = 0; kernel_row < kernel_size; kernel_row++){
                for(int kernel_column = 0; kernel_column < kernel_size; kernel_column++){
                    float pixel = Image.at<uchar>(kernel_row + row - verticalBound,kernel_column + column - horizontalBound) * Kernel[kernel_row][kernel_column];
                    mean += pixel;
                }
            }
            BlurredImage.at<uchar>(row, column) = cvRound(mean);
        }
    }
    return BlurredImage;
}

void GaussianBlurManager::setupKernel(int kernel_size, double sigma) {
    this->kernel_size = kernel_size;
    this->sigma       = sigma;
}

double **GaussianBlurManager::GaussianKernel(int, double) {
    std::cout << "Gaussian kernel by size " << kernel_size << std::endl;
    // Initializing the kernel two-dimensional array
    double **Kernel = new double* [kernel_size];
    for(int row = 0; row < kernel_size; row++)
        Kernel[row] = new double[kernel_size];
    // Initializing the bounds and total value
    double VerticalBound   = (kernel_size - 1) / 2;
    double HorizontalBound = (kernel_size - 1) / 2;
    double total           = 0.;
    // Iterating through the Kernel
    for(int row = 0; row < kernel_size; row++){
        for(int column = 0; column < kernel_size; column++){
            Kernel[row][column] = KernelFunction(row - VerticalBound, column - HorizontalBound, sigma);
            total += Kernel[row][column];
            std::cout << std::left << std::setw(12) << Kernel[row][column] << " ";
        }
        std::cout << std::endl;
    }
    // Normalizing the kernel
    std::cout << "Normalized Gaussian kernel by size " << kernel_size << std::endl;
    for(int row = 0; row < kernel_size; row++){
        for(int column = 0; column < kernel_size; column++){
            Kernel[row][column] = Kernel[row][column] / total;
            std::cout << std::left << std::setw(12) << Kernel[row][column] << " ";
        }
        std::cout << std::endl;
    }
    return Kernel;
}

double GaussianBlurManager::KernelFunction(double x, double y, double sigma) {
    return (1 / (pow(2 * M_PI, static_cast<double>(1 / 2)) * sigma)) * pow(M_E, - (pow(x , 2) + pow(y, 2)) / (2 * pow(sigma, 2)));
}

GaussianBlurManager::~GaussianBlurManager() {

}
