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

void close();

int main() {
    init();
    // MainSystem mainSystem;
    // mainSystem.initialize();
    // mainSystem.runSystems();
    LED redLED(7);
    LED greenLED(5);
    redLED.on();
    greenLED.off();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    redLED.off();
    greenLED.on();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    close();
    return 0;
}

void init() {
    try {
        Logger::init("app.log"); // Adjust the file name as needed
        Logger::logInfo("Application starting");
        // The rest of your program
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialize logger: " << e.what() << std::endl;
    }
}

void close() {
    Logger::close();
}