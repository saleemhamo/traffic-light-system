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

int main() {
    initApplication();

    MainSystem mainSystem;
    mainSystem.initialize();
    mainSystem.runSystems();

    closeApplication(mainSystem);
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