/**
 * @file main.cpp
 * @brief This is the main file of the project
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"
#include <iostream>
#include <string>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread

void init();

// void close();

void myCallback(UltrasonicSensor &ultrasonicSensor) {
    while (true) {
        if (ultrasonicSensor.isMotionDetected()) {
            std::cout << "Motion detected" << std::endl;
        }
        // Consider adding a small delay or an exit condition to avoid spinning too fast
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Example delay
    }
}


int main() {
    init();
    UltrasonicSensor ultrasonicSensor(30, 31);
    ultrasonicSensor.initialize();
    // The line below seems to be incorrect based on the provided context and is commented out
    // ultrasonicSensor.registerMotionCallback(myCallback(ultrasonicSensor));
    std::thread myThread(myCallback, std::ref(ultrasonicSensor));
    myThread.join();

//    MainSystem mainSystem;
//    mainSystem.initialize();
//    mainSystem.runSystems();

    // close();
    return 0;
}


void init() {
    try {
        Logger::init("app.log"); // Adjust the file name as needed
//        Logger::logInfo("Application starting");
        // The rest of your program
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    }
}

// void close(MainSystem mainSystem) {
//     mainSystem.shutdown();
//     Logger::close();
// }