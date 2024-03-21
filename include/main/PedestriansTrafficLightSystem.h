//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"
#include "main/SystemInterface.h"
#include "utils/Constants.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>


class PedestriansTrafficLightSystem : public TrafficLight, public SystemInterface {
private:
    std::atomic<bool> stopRequested;
    std::thread lightThread;
    std::mutex *mtx;
    std::condition_variable *cv;
    bool *signalChanged;

public:
    // Constructor
    PedestriansTrafficLightSystem(std::mutex *mtx, std::condition_variable *cv, bool *signalChanged);

    void requestStop();

    static const int redPin = Constants::PedestriansTrafficLightRedPin;
    static const int greenPin = Constants::PedestriansTrafficLightGreenPin;

    // ISystem interface methods
    void initialize() override;

    void activate() override;

    void deactivate() override;

    // Additional methods specific to pedestrian traffic light system
    void run();  // Function for thread to run
};
