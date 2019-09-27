cmake_minimum_required(VERSION 3.9)
project(Canny-Edge-Detector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(
        Canny-Edge-Detector main.cpp
        canny_edge_detection.cpp
        gaussian_filter.cpp
        sobel_operator.cpp
)

# linking
target_link_libraries(Canny-Edge-Detector ${OpenCV_LIBS})