#include "sensors/CameraSensor.h"
#include <iostream>

CameraSensor::CameraSensor() : running(false), lastDetectionTime(std::chrono::steady_clock::now()) {}

CameraSensor::~CameraSensor() {
    stop();
    if (cap.isOpened()) {
        cap.release();
    }
}

bool CameraSensor::initialize() {
    return cap.open(0);
}

void CameraSensor::run() {
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera." << std::endl;
        return;
    }
    running = true;
    captureThread = std::thread(&CameraSensor::captureLoop, this);
}

void CameraSensor::stop() {
    running = false;
    if (captureThread.joinable()) {
        captureThread.join();
    }
}

void CameraSensor::setMotionDetectedCallback(CallbackType callback) {
    motionDetectedCallback = callback;
}

void CameraSensor::captureLoop() {
    cv::Mat frame, prevFrame, gray, prevGray;
    while (running) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        if (!prevGray.empty()) {
            if (detectMotion(gray, prevGray)) {
                auto now = std::chrono::steady_clock::now();
                if (now - lastDetectionTime > debounceDuration) {
                    lastDetectionTime = now;
                    if (motionDetectedCallback) {
                        motionDetectedCallback();
                    }
                }
            }
        }
        prevGray = gray.clone();
    }
}

bool CameraSensor::detectMotion(cv::Mat& frame, cv::Mat& prevFrame, double sensitivity) {
    cv::Mat diff;
    cv::absdiff(prevFrame, frame, diff);
    cv::threshold(diff, diff, sensitivity, 255, cv::THRESH_BINARY);
    int nonZeroCount = cv::countNonZero(diff);
    return nonZeroCount > 0;
}
