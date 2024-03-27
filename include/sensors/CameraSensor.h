// created by Miguel Rosa on 3/25/2024 //

#endif //_CROSS_GUARD_CAMERASENSOR_H

#ifndef CAMERA_SENSOR_H
#define CAMERA_SENSOR_H

#include <atomic>
#include <thread>
#include <chrono>
#include "WarningSystem.h" // Assuming you have a mechanism to notify the Warning System

class CameraSensor {
public:
    CameraSensor(WarningSystem& warningSystem);
    ~CameraSensor();

    void startDetection();
    void stopDetection();
    bool isCarIncoming() const;

private:
    WarningSystem& warningSystem;
    std::atomic<bool> carDetected;
    std::atomic<bool> stopRequested;
    std::thread detectionThread;

    void detectionLoop();
    bool detectCar(); // Simulates car detection logic
};

#endif // CAMERA_SENSOR_H
