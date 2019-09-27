//
// Created by Dan Orel on 2019-09-27.
//
#include "canny_edge_detection.h"

int main(){
    std::string pathToImage = "/Users/danorel/Workspace/World of C/C++/KMA/MMPI/Canny-Edge-Detector/";
    std::string image = "image1.jpg";
    std::string ImageLabel = "Original Image";
    Mat Image = imread(pathToImage + image, IMREAD_GRAYSCALE);

    imshow(ImageLabel, Image);
    waitKey();
    return 0;
}