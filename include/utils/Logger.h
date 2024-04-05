#ifndef CROSSGUARD_LOGGER
#define CROSSGUARD_LOGGER

#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include "FirestoreLogger.h"

class Logger {
public:
    static const std::string defaultFileName;

    static void init(const std::string &filename = defaultFileName);
    static void start();
    static void stopLogger();
    static void logInfo(const std::string &message);
    static void logError(const std::string &message);
    static void close();

private:
    static std::ofstream logFile;
    static std::vector<std::thread> workers;
    static std::queue<std::function<void()>> tasks;
    static std::mutex queueMutex;
    static std::condition_variable condition;
    static bool stop;

    static void log(const std::string &level, const std::string &message);
    static void threadFunction();
};

#endif //CROSSGUARD_LOGGER
