#include "utils/Logger.h"
#include <iostream>

// Initialize static members
const std::string Logger::defaultFileName = "app.log";
std::ofstream Logger::logFile;
std::vector<std::thread> Logger::workers;
std::queue<std::function<void()>> Logger::tasks;
std::mutex Logger::queueMutex;
std::condition_variable Logger::condition;
bool Logger::stop = false;

void Logger::init(const std::string &filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + filename);
    }
    start();
}

void Logger::start() {
    stop = false;
    for (int i = 0; i < 4; ++i) { // Adjust thread pool size as needed
        workers.emplace_back(threadFunction);
    }
}

void Logger::stopLogger() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker: workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers.clear();
}

void Logger::logInfo(const std::string &message) {
    log("INFO", message);
}

void Logger::logError(const std::string &message) {
    log("ERROR", message);
}

void Logger::close() {
    stopLogger();
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &level, const std::string &message) {
    auto logTask = [level, message]() {
        if (!logFile.is_open()) {
            std::cerr << "Log file is not open." << std::endl;
            return;
        }

        std::time_t now = std::time(nullptr);
        char timestamp[20];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        FirestoreLogger::Log(level, message); // Assume this is the asynchronous operation
        logFile << "[" << timestamp << "] [" << level << "] " << message << std::endl;
    };

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop) {
            throw std::runtime_error("Logger has been stopped.");
        }
        tasks.emplace(logTask);
    }
    condition.notify_one();
}

void Logger::threadFunction() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [] { return stop || !tasks.empty(); });
            if (stop && tasks.empty()) {
                return;
            }
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}
