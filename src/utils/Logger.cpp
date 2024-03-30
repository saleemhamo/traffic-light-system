//
// Created by Saleem Hamo on 26/02/2024.
//
#include "utils/Logger.h"

// Initialize static members
const std::string Logger::defaultFileName = "app.log";
std::ofstream Logger::logFile;

void Logger::init(const std::string &filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + filename);
    }
}

void Logger::logInfo(const std::string &message) {
    log("INFO", message);

}

void Logger::logError(const std::string &message) {
    log("ERROR", message);
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &level, const std::string &message) {
    if (!logFile.is_open()) {
        throw std::runtime_error("Log file is not open.");
    }

    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    FirestoreLogger::Log(level, message);

    logFile << "[" << timestamp << "] [" << level << "] " << message << std::endl;
}
