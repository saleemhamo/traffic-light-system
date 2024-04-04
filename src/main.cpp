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
}