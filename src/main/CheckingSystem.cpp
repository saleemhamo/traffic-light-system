// Documentation by Miguel Rosa

#include "main/CheckingSystem.h"
#include <chrono> // For std::chrono functionalities

/**
 * @file main/CheckingSystem.cpp
 * @brief Implements the CheckingSystem class methods.
 *
 * Provides detailed implementation of each method defined in the CheckingSystem class,
 * including threads for monitoring and managing traffic system interactions.
 */
/**
 * @brief Constructor for the CheckingSystem class.
 * Initializes all member variables and configures sensors with the appropriate pins.
 */

CheckingSystem::CheckingSystem() : isActive(false),
                                   monitorPedestriansActive(false),
                                   monitorRoadsActive(false),
                                   pedestriansButtonEnabled(false),
                                   pedestrianSensor(Constants::CheckingSystemUltrasonic2TriggerPin, Constants::CheckingSystemUltrasonic2EchoPin),
                                   roadSensor(Constants::CheckingSystemUltrasonic1TriggerPin, Constants::CheckingSystemUltrasonic1EchoPin),
                                   pedestriansPushButton(Constants::CheckingSystemButtonPin, EITHER_EDGE, 50) {}


/**
 * @brief Destructor for the CheckingSystem class.
 * Ensures all components are properly deactivated and threads are joined before destruction.
 */

CheckingSystem::~CheckingSystem() {
    deactivate(); // Ensure threads are properly joined and sensors are deactivated
}

/**
 * @brief Initializes sensors and registers button press callbacks.
 * Configures and initializes all associated sensors and registers callback for the pedestrian button.
 */
void CheckingSystem::initialize() {
    // Initialize sensors and register button press callbacks
    pedestrianSensor.initialize();
    roadSensor.initialize();
    pedestriansPushButton.initialize();
    pedestriansPushButton.registerButtonPressCallback([this]() { this->onPedestriansButtonPress(); });
}

/**
 * @brief Main operation function which activates all systems and starts monitoring.
 * Launches threads for pedestrian and road monitoring and waits for them to complete.
 *
 * This method initializes the active monitoring process for both pedestrians and vehicles.
 * It starts two threads: one for pedestrian monitoring and another for road monitoring.
 * Both threads are joined to ensure that the system continues running until both monitoring processes complete.
 *
 * @note This function must be called after all sensors and callbacks are properly initialized.
 *       It will block until all monitoring threads complete, which means it should ideally
 *       be run in its own thread if the application must perform other tasks concurrently.
 *
 * @throws std::system_error if thread creation fails.
 * @see initialize(), enableSensing(), disableSensing()
 */
void CheckingSystem::run() {
    isActive = true;

    enablePedestriansMotionDetection();
    enablePedestriansButton();
    enableCarsMotionDetection();

    // Launch monitoring threads
    std::thread pedestrianThread([this]() { this->monitorPedestrian(); });
    std::thread roadThread([this]() { this->monitorRoad(); });
    std::thread buttonThread([this]() { this->monitorPedestriansButton(); });

    // Threads are joined to ensure the system does not exit prematurely
    pedestrianThread.join();
    roadThread.join();
}

// TODO: {Saleem & Alex}
void CheckingSystem::monitorPedestriansButton() {
    if (pedestriansButtonClicked) {
        pedestriansButtonClicked(); // Call the registered callback
    }
}

/**
 * @brief Handles actions to be performed when the pedestrian button is pressed.
 * If the button is enabled and the callback is set, it triggers the registered callback.
 */
void CheckingSystem::onPedestriansButtonPress() {
    if (pedestriansButtonEnabled && pedestriansButtonClicked) {
        pedestriansButtonClicked();
    }
}

/**
 * @brief Monitors pedestrian activity continuously.
 * Checks for motion detection and triggers callbacks if motion is detected.
 * Runs in a dedicated thread and loops until isActive is false.
 *
 * @note This function is intended to run in a separate thread to avoid blocking the main application flow.
 */
void CheckingSystem::monitorPedestrian() {
    while (isActive) {
        if (monitorPedestriansActive && pedestrianSensor.isMotionDetected()) {
            if (pedestriansMotionDetected) {
                pedestriansMotionDetected(); // Call the registered callback
            }
        }
        // Sleep to prevent hogging CPU - adjust the delay as needed
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

/**
 * @brief Monitors road traffic continuously.
 * Similar to monitorPedestrian, it checks for motion and triggers callbacks.
 * Runs in a dedicated thread and loops until isActive is false.
 *
 * @note Designed to run in a background thread, independently of other system operations.
 */
void CheckingSystem::monitorRoad() {
    while (isActive) {
        if (monitorRoadsActive && roadSensor.isMotionDetected()) {
            if (carsMotionDetected) {
                carsMotionDetected(); // Call the registered callback
            }
        }
        // Sleep to prevent hogging CPU - adjust the delay as needed
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

bool CheckingSystem::isRoadMotionDetected() {
    return roadSensor.isMotionDetected();
}

/**
 * @brief Deactivates the system and ensures a clean shutdown.
 * Sets isActive to false and waits for a brief period to allow threads to finish gracefully.
 */
void CheckingSystem::deactivate() {
    isActive = false;
    // Give time for threads to finish any ongoing work
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust as needed
    // No need to manually join the threads since they were detached,
    // but ensure any needed cleanup is performed here.
}

/**
 * @brief Enables the motion detection for pedestrians.
 */
void CheckingSystem::enablePedestriansMotionDetection() {
    monitorRoadsActive = true;
}

/**
 * @brief Disables the motion detection for pedestrians.
 */
void CheckingSystem::disablePedestriansMotionDetection() {
    monitorRoadsActive = false;
}

/**
 * @brief Enables the motion detection for cars.
 */
void CheckingSystem::enableCarsMotionDetection() {
    monitorPedestriansActive = true;
}

/**
 * @brief Disables the motion detection for cars.
 */
void CheckingSystem::disableCarsMotionDetection() {
    monitorRoadsActive = false;
}

/**
 * @brief Enables the use of the pedestrian button.
 */
void CheckingSystem::enablePedestriansButton() {
    pedestriansButtonEnabled = true;
}

/**
 * @brief Disables the pedestrian button to prevent its use.
 */
void CheckingSystem::disablePedestriansButton() {
    pedestriansButtonEnabled = false;
}

/**
 * @brief Registers a callback function for car motion detection.
 * @param callback Function to call when car motion is detected.
 */
void CheckingSystem::registerCarsMotionCallback(const std::function<void()> &callback) {
    Logger::logInfo("MainSystem::initialize called");
    carsMotionDetected = callback;
}

/**
 * @brief Registers a callback function for pedestrian motion detection.
 * @param callback Function to call when pedestrian motion is detected.
 */
void CheckingSystem::registerPedestriansMotionCallback(const std::function<void()> &callback) {
    pedestriansMotionDetected = callback;
}

/**
 * @brief Registers a callback function for pedestrian button press.
 * @param callback Function to call when the pedestrian button is pressed.
 */
void CheckingSystem::registerPedestriansButtonCallback(const std::function<void()> &callback) {
    pedestriansButtonClicked = callback;
}

/**
 * @brief Activates all sensors and detection mechanisms in the system.
 * Calls individual enable methods for pedestrian and vehicle detection and button usage.
 */
void CheckingSystem::enableSensing() {
    enablePedestriansButton();
    enablePedestriansMotionDetection();
    enableCarsMotionDetection();
}

/**
 * @brief Deactivates all sensors and detection mechanisms in the system.
 * Calls individual disable methods for pedestrian and vehicle detection and button usage.
 */
void CheckingSystem::disableSensing() {
    disablePedestriansButton();
    disablePedestriansMotionDetection();
    disableCarsMotionDetection();
}
