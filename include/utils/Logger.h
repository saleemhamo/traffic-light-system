/**
 * @file Logger.h
 * @brief Defines the Logger class which provides logging functionalities both locally and to Firestore.
 *
 * This class encapsulates methods for initializing, starting, stopping, and logging messages to a local file 
 * and Google Firestore. It uses asynchronous logging with multiple worker threads to manage writing operations 
 * without blocking the main application flow.
 */

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


/**
 * @class Logger
 * @brief Provides a thread-safe logging mechanism that writes messages to a file and Google Firestore.
 *
 * Logger is designed to be used across different parts of an application to log various messages like 
 * information and errors. It supports simultaneous file and Firestore logging and handles concurrent access 
 * using a queue-based system with multiple worker threads.
 */
class Logger {
public:
    static const std::string defaultFileName; ///< Default filename for local log files.

    /**
     * @brief Initializes the Logger with the specified file name.
     * @param filename Name of the file to which logs will be written. Defaults to 'defaultFileName'.
     */
    static void init(const std::string &filename = defaultFileName);

    /**
     * @brief Starts the logging process by spawning worker threads.
     * 
     * Initializes worker threads that handle asynchronous log writing. Must be called after init.
     */
    static void start();

    /**
     * @brief Stops all logging activity.
     *
     * Signals worker threads to complete their tasks and stop running.
     */
    static void stopLogger();

    /**
     * @brief Logs an informational message.
     * @param message The info message to log.
     */
    static void logInfo(const std::string &message);

    /**
     * @brief Logs an error message.
     * @param message The error message to log.
     */
    static void logError(const std::string &message);

    /**
     * @brief Closes the Logger and cleans up resources.
     *
     * Ensures all logging activities are stopped and resources are released properly.
     */
    static void close();

private:
    static std::ofstream logFile; ///< Output stream for the log file.
    static std::vector<std::thread> workers; ///< Worker threads for processing log tasks.
    static std::queue<std::function<void()>> tasks; ///< Queue of log tasks.
    static std::mutex queueMutex; ///< Mutex for protecting access to the tasks queue.
    static std::condition_variable condition; ///< Condition variable for notifying worker threads.
    static bool stop; ///< Flag indicating whether logging should be stopped.

    /**
     * @brief Logs a message with the specified level.
     * @param level The level of the log (e.g., "INFO", "ERROR").
     * @param message The message to log.
     */
    static void log(const std::string &level, const std::string &message);

    /**
     * @brief Function that runs within worker threads to process logging tasks.
     *
     * Continuously processes tasks from the queue until stopped.
     */
    static void threadFunction();
};

#endif // CROSSGUARD_LOGGER