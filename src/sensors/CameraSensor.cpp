//
// Created by Miguel Rosa on 03/26/2024

#include "CameraSensor.h"
#include "WarningSystem.h"definition of checkingsystem
#include <opencv2/opencv.hpp>

CameraSensor::CameraSensor(WarningSystem& system) 
: warningSystem(system), movementDetected(false), stopRequested(false) {
    // Initialize the camera
    camera.set(CV_CAP_PROP_FORMAT, CV_8UC1); // Use gray scale for faster processing
    if (!camera.open()) {
        throw std::runtime_error("Could not open camera");
    }
}

CameraSensor::~CameraSensor() {
    stopDetection();
    camera.release();
}

void CameraSensor::startDetection() {
    if (detectionThread.joinable()) return; // Detection already running

    stopRequested = false;
    detectionThread = std::thread(&CameraSensor::detectionLoop, this);
}

void CameraSensor::stopDetection() {
    stopRequested = true;
    if (detectionThread.joinable()) {
        detectionThread.join();
    }
}

bool CameraSensor::isMovementDetected() const {
    return movementDetected.load();
}

void CameraSensor::detectionLoop() {
    cv::Mat frame;
    while (!stopRequested) {
        // Assuming Libcam2OpenCV provides a method to capture a frame
        if (camera.capture(frame)) { // This method needs to be defined in Libcam2OpenCV
            cv::GaussianBlur(frame, frame, cv::Size(21, 21), 0);

            static cv::Mat prevFrame;
            if (!prevFrame.empty()) {
                cv::Mat frameDelta, thresh;
                cv::absdiff(prevFrame, frame, frameDelta);
                cv::threshold(frameDelta, thresh, 25, 255, cv::THRESH_BINARY);
                cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);

                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(thresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

                movementDetected = !contours.empty();
                if (movementDetected) {
                    warningSystem.notifyEvent(); // Notify the warning system
                }
            }
            prevFrame = frame.clone();
        }
    }
}

