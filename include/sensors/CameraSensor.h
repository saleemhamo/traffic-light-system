// created by Miguel Rosa on 3/25/2024 //

#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Libcam2OpenCV.h"

class WarningSystem; // Forward declaration

class CameraSensor {
public:
    CameraSensor(WarningSystem& warningSystem);
    ~CameraSensor();

    void startDetection();
    void stopDetection();
    bool isMovementDetected() const;

private:
    WarningSystem& warningSystem;
    std::atomic<bool> movementDetected;
    std::atomic<bool> stopRequested;
    std::thread detectionThread;
    Libcam2OpenCV camera;

    void detectionLoop();
};

#endif // CAMERA_SENSOR_H
