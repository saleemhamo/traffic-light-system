//
// Created by Saleem Hamo on 26/02/2024.
//

#ifndef CROSSGUARD_LOGGER_CPP
#define CROSSGUARD_LOGGER_CPP

#include <iostream>

class Logger {

public:
    static void logInfo(const std::string &message) {
        std::cout << "INFO: " << message << std::endl;
    }

    static void logError(const std::string &message) {
        std::cerr << "ERROR: " << message << std::endl;
    }
};

#endif
// TODO: Add file logger
//#include <fstream>
//#include <string>
//
//class Logger {
//private:
//    std::ofstream logFile;
//
//public:
//    Logger(const std::string& filename) {
//        logFile.open(filename, std::ios::app); // Open in append mode
//    }
//
//    ~Logger() {
//        if (logFile.is_open()) {
//            logFile.close();
//        }
//    }
//
//    void log(const std::string& message) {
//        if (logFile.is_open()) {
//            logFile << message << std::endl;
//        }
//    }
//};

//Logger logger("app.log");
//logger.log("This is a log message.");