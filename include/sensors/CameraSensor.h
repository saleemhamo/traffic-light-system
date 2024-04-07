// created by Miguel Rosa on 3/25/2024 //
#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "Libcam2OpenCV.h"
#include <opencv2/opencv.hpp>

class CameraSensor {
public:
    CameraSensor();
    ~CameraSensor();

    // Start the camera sensor
    void start();

    // Stop the camera sensor
    void stop();

    // Set a callback for motion detection
    void setMotionCallback(std::function<void()> callback);

private:
    Libcam2OpenCV camera;
    cv::Mat prevFrame;
    std::function<void()> motionCallback;

    // Internal callback for frame processing
    void processFrame(const cv::Mat& frame);

    // Method to check for motion between frames
    bool detectMotion(const cv::Mat& prev, const cv::Mat& current);
};

#endif // CAMERASENSOR_H
