//
// Created by Miguel Rosa on 03/26/2024
#include "sensors/CameraSensor.h"

CameraSensor::CameraSensor() {
    // Configure the frame callback of the Libcam2OpenCV instance
    camera.setFrameCallback([this](const cv::Mat &frame) {
        this->processFrame(frame);
    });
}

CameraSensor::~CameraSensor() {
    stop();
}

void CameraSensor::start() {
    camera.start();
}

void CameraSensor::stop() {
    camera.stop();
}

void CameraSensor::setMotionCallback(std::function<void()> callback) {
    motionCallback = std::move(callback);
}

void CameraSensor::processFrame(const cv::Mat &frame) {
    if (!prevFrame.empty()) {
        if (detectMotion(prevFrame, frame)) {
            if (motionCallback) {
                motionCallback();
            }
        }
    }
    prevFrame = frame.clone();
}

bool CameraSensor::detectMotion(const cv::Mat &prev, const cv::Mat &current) {
    cv::Mat diff, thresh;
    cv::absdiff(prev, current, diff);
    cv::cvtColor(diff, diff, cv::COLOR_BGR2GRAY);
    cv::threshold(diff, thresh, 25, 255, cv::THRESH_BINARY);
    cv::dilate(thresh, thresh, cv::Mat(), cv::Point(-1, -1), 2);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Consider motion detected if contours are found
    return !contours.empty();
}
