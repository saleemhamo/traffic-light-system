cmake_minimum_required(VERSION 3.27)
project(MotionDetection)

set(CMAKE_CXX_STANDARD 11)


# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include directories for OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(MotionDetection main.cpp)


# Link OpenCV libraries
target_link_libraries(MotionDetection ${OpenCV_LIBS})
