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
    MainSystem mainSystem;
    mainSystem.initialize();
    mainSystem.runSystems();

    // Keep the application running in a loop
    std::string command;
    while (true) {
        // Here, for simplicity, we just sleep and keep the program alive
        // In a real application, you might check for input to shut down,
        // monitor system status, or perform other background tasks.
        //        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for a bit to reduce CPU usage

        // Example: Check for a termination command or condition
        std::cout << "Type 'exit' to stop the system: ";
        std::getline(std::cin, command);
        if (command == "exit") {
            break; // Exit the loop if 'exit' command is given
        }
    }

    // Implement any necessary cleanup before shutting down
    // Note: Depending on your system's requirements, you might need to properly
    // shut down subsystems or handle other cleanup tasks here.

    close();
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

void close() {
    Logger::close();
}