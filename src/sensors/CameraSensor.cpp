//
// Created by Miguel Rosa on 03/26/2024

#include "CameraSensor.h"

CameraSensor::CameraSensor(WarningSystem& system) : warningSystem(system), carDetected(false), stopRequested(false) {}

CameraSensor::~CameraSensor() {
    stopDetection();
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

bool CameraSensor::isCarIncoming() const {
    return carDetected.load();
}

void CameraSensor::detectionLoop() {
    while (!stopRequested) {
        // Assume fetchNewFrame is a method that blocks until a new frame is available. This method should ideally be non-CPU-intensive, possibly waiting on an event or interrupt.
        auto frame = fetchNewFrame();

        if (detectCar(frame)) { // Now detectCar takes the new frame as input
            carDetected = true;
            warningSystem.notifyEvent(); // Notify the warning system
        } else {
            carDetected = false;
        }
    }
}

bool CameraSensor::detectCar(const FrameType& frame) {
    // Implement your frame-based car detection logic here
    return false; // Placeholder return
}

// Assume FrameType is defined elsewhere according to your camera library or API
FrameType CameraSensor::fetchNewFrame() {
    FrameType frame;
    // Blocking call to fetch a new frame from the camera
    // This could be an actual camera API call that blocks until a new frame is available
    return frame;
}

