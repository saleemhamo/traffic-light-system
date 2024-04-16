/**
 * @file main.cpp
 * @brief Main entry point for the application. Initializes the application, runs the main system, and then performs cleanup upon exit.
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"
#include "utils/FirestoreLogger.h"
#include <iostream>
#include <string>

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
    cameraWrapper.setMotionDetectedCallback([]
                                            { std::cout << "Motion detected!" << std::endl; });
    cameraWrapper.start();

    // Wait for the user to stop the program
    std::cout << "Press Enter to stop the program..." << std::endl;
    std::string line;
    std::getline(std::cin, line);

    cameraWrapper.stop();
    return 0;
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

    try {
        Logger::logInfo("Application stopping");
        Logger::close();
    } catch (const std::exception &e) {
        std::cerr << "Failed to close logger: " << e.what() << std::endl;
    }


}