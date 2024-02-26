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

class CarsTrafficLightSystem : public TrafficLight, public SystemInterface {
private:
    std::mutex *mtx;
    std::condition_variable *cv;
    bool *signalChanged;
    bool stopRequested;
    std::thread lightThread;

public:
    // Constructor
    CarsTrafficLightSystem(std::mutex *mtx, std::condition_variable *cv, bool *signalChanged);

    void requestStop();

    static const int redPin = Constants::CarsTrafficLightRedPin;
    static const int greenPin = Constants::CarsTrafficLightGreenPin;


    // ISystem interface methods
    void initialize() override;

    void activate() override;

    void deactivate() override;

    // Additional methods specific to car traffic light system
    void run();  // Function for thread to run
};
