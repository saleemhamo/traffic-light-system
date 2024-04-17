/**
 * @file main.cpp
 * @brief Main entry point for the application. Initializes the application, runs the main system, and then performs cleanup upon exit.
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"
#include "utils/FirestoreLogger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

/**
 * @brief Initializes the application's logging systems.
 *
 * This function initializes the FirestoreLogger and Logger to begin logging application events. It attempts to connect to Firestore for logging and sets up a local log file.
 */
void initApplication();

/**
 * @brief Shuts down the application, ensuring graceful termination of systems and logging.
 *
 * @param mainSystem Reference to the MainSystem object to shut down.
 */
void closeApplication(MainSystem &mainSystem);

/**
 * @brief The main function of the application.
 *
 * Initializes the application, creates and runs the main system, and then closes the application on completion.
 * @return int The exit code of the application, where 0 indicates successful termination.
 */
void motionDetected() {
    std::cout << "Motion detected!" << std::endl;
}

int main() {
    initApplication();
    CameraWrapper cameraWrapper;

    // Test setting a motion detection callback
    bool motionDetected = false;
    cameraWrapper.setMotionDetectedCallback([&]()
                                            {
        std::cout << "Motion detected!" << std::endl;
        motionDetected = true; });

    // Start the camera
    Libcam2OpenCVSettings settings;
    settings.width = 640;
    settings.height = 480;
    settings.framerate = 30;
    cameraWrapper.start(settings);

    // Wait for 10 seconds
    std::cout << "Capturing for 10 seconds..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Stop the camera
    cameraWrapper.stop();

    // Check if motion was detected
    if (motionDetected)
    {
        std::cout << "Motion detection test passed" << std::endl;
    }
    else
    {
        std::cout << "Motion detection test failed" << std::endl;
    }

    return 0;

    // CameraWrapper cameraWrapper;
    // cameraWrapper.setMotionDetectedCallback([]
    //                                         { std::cout << "Motion detected!" << std::endl; });
    // cameraWrapper.start();

    // // Wait for the user to stop the program
    // std::cout << "Press Enter to stop the program..." << std::endl;
    // std::string line;
    // std::getline(std::cin, line);

    // cameraWrapper.stop();
    // return 0;

    // NOT WORKING
    // CameraSensor camera;
    // if (camera.initialize()) {
    //     camera.setMotionDetectedCallback(motionDetected);
    //     camera.run();

    //     // Keep the main thread running to simulate prolonged observation
    //     std::this_thread::sleep_for(std::chrono::minutes(10));

    //     camera.stop();
    // } else {
    //     std::cerr << "Failed to initialize the camera." << std::endl;
    // }

    // return 0;

//    MainSystem mainSystem;
//    mainSystem.initialize();
//    mainSystem.runSystems();
//
//    closeApplication(mainSystem);
    return 0;
}

void initApplication() {
    try {
        FirestoreLogger::Initialize("INITIALIZE");
        FirestoreLogger::Log("INFO", "Application Started!");
    }
    catch (const std::exception &e) {
        std::cerr << "Failed to connect to firebase: " << e.what() << std::endl;
    }

    try {
        Logger::init("app.log");
        Logger::logInfo("Application starting");
    }
    catch (const std::exception &e) {
        std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    }
}

void closeApplication(MainSystem &mainSystem) {
    mainSystem.shutdown();
    // Logger::close(); //why there's another loger here when try catch already handles that?

    try {
        Logger::logInfo("Application stopping");
        Logger::close();
    }
    catch (const std::exception &e) {
        std::cerr << "Failed to close logger: " << e.what() << std::endl;
    }
}