/**
 * @file MainSystem.cpp
 * @brief Implementation of the MainSystem class.
 * The MainSystem class is responsible for managing the overall operation of the traffic light system. It initializes all subsystems, runs them, and shuts them down. It also handles callbacks from the CheckingSystem and manages the traffic light state.
 * @author (Alex)
 * @version 1.0
 */

#include "main/MainSystem.h"
#include "utils/Logger.h"

/**
 * @brief Construct a new Main System:: Main System object
 * Initializes the traffic light state to OFF.
 */
MainSystem::MainSystem() : trafficLightState(OFF) {}

/**
 * @brief Destruct a new Main System:: Main System object
 * Shuts down all subsystems.
 */
MainSystem::~MainSystem()
{
    shutdown();
}

/**
 * @brief Initializes all subsystems.
 * This function initializes all subsystems of the traffic light system.
 */
void MainSystem::initialize()
{
    // Initialize all subsystems here
    Logger::logInfo("MainSystem::initialize called");
    carsTrafficLight.initialize();
    pedestriansTrafficLight.initialize();
    checkingSystem.initialize();
    warningSystem.initialize();

    // Register callbacks from the CheckingSystem
    checkingSystem.registerCarsMotionCallback([this]()
                                              { this->onCarsMotionDetected(); });
    checkingSystem.registerPedestriansMotionCallback([this]()
                                                     { this->onPedestriansMotionDetected(); });
    checkingSystem.registerPedestriansButtonCallback([this]()
                                                     { this->onPedestriansButtonClicked(); });
}

/**
 * @brief Runs all subsystems.
 * This function runs all subsystems of the traffic light system.
 */
void MainSystem::runSystems()
{
    enableTrafficLightsNormalBehaviour();
    std::thread trafficLightsThread(&MainSystem::runTrafficLightsNormalBehaviour, this);
    std::thread checkingSystemThread([this]()
                                     { checkingSystem.run(); });
    trafficLightsThread.join();
    checkingSystemThread.join();
    // Enable running warning system if needed
}

/**
 * @brief Shuts down all subsystems.
 * This function shuts down all subsystems of the traffic light system.
 */
void MainSystem::shutdown()
{
    carsTrafficLight.deactivate();
    pedestriansTrafficLight.deactivate();
    checkingSystem.deactivate();
    warningSystem.deactivate();
    // Join all threads here if they are joinable
}

/**
 * @brief Callback for when cars motion is detected.
 * This function is called when the CheckingSystem detects motion from cars. It checks the current traffic light state and takes appropriate action.
 */
void MainSystem::onCarsMotionDetected()
{
    Logger::logInfo("Cars motion detected");
    std::cout << "Cars motion detected" << std::endl;
    if (trafficLightState != CARS_RED_PEDESTRIANS_GREEN)
    {
        return; // Do Nothing
    }

    // State is CARS_RED_PEDESTRIANS_GREEN
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllTrafficLightsRed();
    warningSystem.activate();

    // after 10 seconds
    mainSystemTimer.setTimeout([this]
                               {
        warningSystem.deactivate();
        enableTrafficLightsNormalBehaviour();
        runTrafficLightsNormalBehaviour();
        checkingSystem.enableSensing(); }, 10000);
}

/**
 * @brief Callback for when pedestrians motion is detected.
 * This function is called when the CheckingSystem detects motion from pedestrians. It checks the current traffic light state and takes appropriate action.
 */
void MainSystem::onPedestriansMotionDetected()
{
    Logger::logInfo("Pedestrians motion detected");
    std::cout << "Pedestrians motion detected" << std::endl;
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED)
    {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllTrafficLightsRed();
    warningSystem.activate();

    // after 10 seconds
    mainSystemTimer.setTimeout([this]
                               {
        warningSystem.deactivate();
        enableTrafficLightsNormalBehaviour();
        runTrafficLightsNormalBehaviour();
        checkingSystem.enableSensing(); }, 10000);
}

/**
 * @brief Callback for when the pedestrians button is clicked.
 * This function is called when the CheckingSystem detects a click on the pedestrians button. It checks the current traffic light state and takes appropriate action.
 */
void MainSystem::onPedestriansButtonClicked()
{
    std::cout << "Pedestrians button clicked" << std::endl;
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED)
    {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    // if road status is empty (sensor or camera) -> turn to CARS_RED_PEDESTRIANS_GREEN
    // continue normal behaviour
}

/**
 * @brief Enables the normal behaviour of traffic lights.
 * This function enables the normal operation of traffic lights.
 */
void MainSystem::enableTrafficLightsNormalBehaviour()
{
    isTrafficLightRunningInNormalBehaviour = true;
}

/**
 * @brief Disables the normal behaviour of traffic lights.
 * This function disables the normal operation of traffic lights.
 */
void MainSystem::disableTrafficLightsNormalBehaviour()
{
    isTrafficLightRunningInNormalBehaviour = false;
    carsTrafficLightTimer.stopTimer();
    pedestriansTrafficLightTimer.stopTimer();
    yellowTrafficLightTimer.stopTimer();
}

/**
 * @brief Turns the cars traffic light green.
 * This function turns the cars traffic light green and initiates a sequence for pedestrians traffic light.
 */
void MainSystem::turnCarsTrafficLightGreen()
{
    Logger::logInfo("turnCarsTrafficLightGreen called");
    if (!isTrafficLightRunningInNormalBehaviour)
    {
        return;
    }
    carsTrafficLight.turnYellow();
    pedestriansTrafficLight.turnRed();
    yellowTrafficLightTimer.setTimeout([this]
                                       {
        carsTrafficLight.turnGreen();
        pedestriansTrafficLight.turnRed();
        trafficLightState = CARS_GREEN_PEDESTRIANS_RED;
        pedestriansTrafficLightTimer.setTimeout([this] { turnPedestriansTrafficLightGreen(); }, 20000); }, 2000);

    Logger::logInfo("turnCarsTrafficLightGreen finished");
}

/**
 * @brief Turns the pedestrians traffic light green.
 * This function turns the pedestrians traffic light green and initiates a sequence for cars traffic light.
 */
void MainSystem::turnPedestriansTrafficLightGreen()
{
    Logger::logInfo("turnPedestriansTrafficLightGreen called");
    if (!isTrafficLightRunningInNormalBehaviour)
    {
        return;
    }
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnGreen();
    trafficLightState = CARS_RED_PEDESTRIANS_GREEN;
    carsTrafficLightTimer.setTimeout([this]
                                     { turnCarsTrafficLightGreen(); }, 20000);
    Logger::logInfo("turnPedestriansTrafficLightGreen finished");
}

/**
 * @brief Turns all traffic lights red.
 * This function turns all traffic lights red, stopping both car and pedestrian traffic.
 */
void MainSystem::turnAllTrafficLightsRed()
{
    Logger::logInfo("turnAllTrafficLightsRed called");
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnRed();
    trafficLightState = OFF;
}

/**
 * @brief Runs the normal behavior of traffic lights.
 * This function initiates the normal operation of traffic lights.
 */
void MainSystem::runTrafficLightsNormalBehaviour()
{
    Logger::logInfo("runTrafficLightsNormalBehaviour called");
    turnCarsTrafficLightGreen();
}