//
// Created by Miguel Rosa on 03/26/2024

#include "CameraSensor.h"
#include "CheckingSystem.h" // Include the definition of checkingsystem
#include <opencv2/opencv.hpp>

CameraSensor::CameraSensor(checkingsystem& system) 
: checkingSystem(system), movementDetected(false), stopRequested(false) {
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
    cv::Mat frame, prevFrame, frameDelta, thresh;
    while (!stopRequested) {
        if (camera.grab()) {
            camera.retrieve(frame);
            cv::GaussianBlur(frame, frame, cv::Size(21, 21), 0);
            
            if (!prevFrame.empty()) {
                cv::absdiff(prevFrame, frame, frameDelta);
                cv::threshold(frameDelta, thresh, 25, 255, CV_THRESH_BINARY);
                cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);
                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(thresh.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

                if (!contours.empty()) {
                    movementDetected = true;
                    checkingsystem.notifyEvent(); // Assume checkingsystem has a notifyEvent() method
                } else {
                    movementDetected = false;
                }
            }
            prevFrame = frame.clone();
        }
    }
}

