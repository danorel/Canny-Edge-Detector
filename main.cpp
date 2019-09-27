//
// Created by Dan Orel on 2019-09-27.
//
#include "hands_methods.h"

int main(){
    std::string pathToImage = "/Users/danorel/Workspace/World of C/C++/KMA/MMPI";
    std::string image = "image.jpg";
    std::string ImageLabel = "Original Image";
    Mat Image = imread(pathToImage + image, IMREAD_GRAYSCALE);

    imshow(ImageLabel, Image);
    waitKey();
    return 0;
}