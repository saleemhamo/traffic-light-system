/**
 * @file main.cpp
 * @brief This is the main file of the project
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"
#include <iostream>
#include <string>

void initApplication();

void closeApplication(MainSystem &mainSystem);

void callback() {
    std::cout << "Motion detected" << std::endl;
}

int main() {
    initApplication();

    MainSystem mainSystem;
    mainSystem.initialize();
    mainSystem.runSystems();

//    UltrasonicSensor ultrasonicSensor(23, 24);
//    ultrasonicSensor.initialize();
////    ultrasonicSensor.registerMotionCallback(callback);
//
//    while (true) {
//        if (ultrasonicSensor.isMotionDetected(0.1)) {
//            std::cout << "Motion detected inside the loop" << std::endl;
//        }
//    }

    closeApplication(mainSystem);
    return 0;
}


void initApplication() {
    try {
        Logger::init("app.log"); // Adjust the file name as needed
        Logger::logInfo("Application starting");
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    }
}

void closeApplication(MainSystem &mainSystem) {
    mainSystem.shutdown();
    Logger::close();
}