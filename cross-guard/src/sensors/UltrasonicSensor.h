//
// Created by Saleem Hamo on 07/02/2024.
//

#include <atomic>  // For std::atomic

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);

    ~UltrasonicSensor();

    void initialize();

    double getDistance();  // Returns the distance measured by the sensor

private:
    int triggerPin;
    int echoPin;
    std::atomic<bool> isInitialized{false};
};

