/**
 * @file main.cpp
 * @brief This is the main file of the project
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"
#include "utils/FirestoreLogger.h"
#include <iostream>
#include <string>

void initApplication();

void closeApplication(MainSystem &mainSystem);

void callback() {
    std::cout << "Button clicked" << std::endl;
}

int main() {
    initApplication();
    WarningSystem warningSystem;
    CameraSensor cameraSensor(warningSystem);

    std::cout << "Starting motion detection..." << std::endl;
    cameraSensor.startDetection();

    // Run the main loop for 60 seconds
    auto startTime = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - startTime).count() < 60)
    {
        // Check if motion was detected
        if (cameraSensor.isMovementDetected())
        {
            std::cout << "Movement detected!" << std::endl;
        }

        // Sleep for a short duration to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Stopping motion detection..." << std::endl;
    cameraSensor.stopDetection();


//    MainSystem mainSystem;
//    mainSystem.initialize();
//    mainSystem.runSystems();

//    closeApplication(mainSystem);
    return 0;
}


void initApplication() {
    try {
        FirestoreLogger::Initialize("INITIALIZE");
        FirestoreLogger::Log("INFO", "Application Started!");
    } catch (const std::exception &e) {
        std::cerr << "Failed to connect to firebase: " << e.what() << std::endl;
    }

    try {
        Logger::init("app.log");
        Logger::logInfo("Application starting");
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    }
}

void closeApplication(MainSystem &mainSystem) {
    mainSystem.shutdown();
    Logger::close();
}