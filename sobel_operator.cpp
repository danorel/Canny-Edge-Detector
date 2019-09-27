//
// Created by Dan Orel on 2019-09-27.
//
#include "sobel_operator.h"

SobelOperator::SobelOperator(const Mat& Image){
    this->Image = Image;
}

Mat SobelOperator::process(){
    // Setting up the kernel size length
    const int kernel_size = 3;
    // Initializing the processed image
    Mat ProcessedImage(Image.size(), CV_8UC1);
    int columns = Image.cols;
    int rows = Image.rows;
    // Defining the shifts to the kernels
    int verticalBound = (kernel_size - 1) / 2;
    int horizontalBound = (kernel_size - 1) / 2;
    // Initializing the Gx and Gy kernels
    double **Gx_Kernel = Gx();
    double **Gy_Kernel = Gy();
    for(int row = 0 + verticalBound; row < rows - verticalBound; row++){
        for(int column = 0 + horizontalBound; column < columns - horizontalBound; column++){
            float total = 0., x_total = 0., y_total = 0.;
            for(int kernel_row = 0; kernel_row < kernel_size; kernel_row++){
                for(int kernel_column = 0; kernel_column < kernel_size; kernel_column++){
                    float x_operator = Image.at<uchar>(kernel_row + row - verticalBound, kernel_column + column - horizontalBound) * Gx_Kernel[kernel_row][kernel_column];
                    float y_operator = Image.at<uchar>(kernel_row + row - verticalBound, kernel_column + column - horizontalBound) * Gy_Kernel[kernel_row][kernel_column];
                    x_total += x_operator;
                    y_total += y_operator;
                }
            }
            total = sqrt(pow(x_total, 2) + pow(y_total, 2));
            if(total > 255)
                ProcessedImage.at<uchar>(row, column) = 255;
            else if(total < 0)
                ProcessedImage.at<uchar>(row, column) = 0;
            else
                ProcessedImage.at<uchar>(row, column) = total;
        }
    }
    return ProcessedImage;
}

double** SobelOperator::Gx(){
    const short size = 3;
    // Initializing the Gx
    double **Gx = new double*[size];
    for(int row = 0; row < size; row++){
        Gx[row] = new double[size];
    }
    double Gx_Temp[][size] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };
    for(int row = 0; row < size; row++){
        for(int column = 0; column < size; column++){
            Gx[row][column] = Gx_Temp[row][column];
        }
    }
    // Output Gx operator
    std::cout << "Gx operator " << std::endl;
    for(int row = 0; row < size; row++){
        for(int column = 0; column < size; column++){
            std::cout << std::left << std::setw(2) << Gx[row][column] << " ";
        }
        std::cout << std::endl;
    }
    return Gx;
}

double** SobelOperator::Gy(){
    const short size = 3;
    // Initializing the Gy
    double **Gy = new double*[size];
    for(int row = 0; row < size; row++){
        Gy[row] = new double[size];
    }
    double Gy_Temp[][size] = {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
    };
    for(int row = 0; row < size; row++){
        for(int column = 0; column < size; column++){
            Gy[row][column] = Gy_Temp[row][column];
        }
    }
    // Output Gy operator
    std::cout << "Gy operator " << std::endl;
    for(int row = 0; row < size; row++){
        for(int column = 0; column < size; column++){
            std::cout << std::left << std::setw(2) << Gy[row][column] << " ";
        }
        std::cout << std::endl;
    }
    return Gy;
}

SobelOperator::~SobelOperator() {

}
