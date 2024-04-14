//
// Edited and documented by Miguel Rosa
//

/**
 * @file FirestoreLogger.h
 * @brief Provides functionality to log messages to Google Firestore.
 *
 * This class defines a static logger that can initialize a connection to Google Firestore
 * using an API key and log messages with different severity levels. The log entries are
 * timestamped and pushed to a Firestore database.
 */

#ifndef FIRESTORELOGGER_H
#define FIRESTORELOGGER_H

#include <string>
#include <cpr/cpr.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

/**
 * @class FirestoreLogger
 * @brief Logger class for sending logs to Google Firestore.
 *
 * FirestoreLogger uses the CPR library to send HTTP requests to Firestore. It requires an
 * API key for authentication and sends log data to a specified Firestore database.
 */
class FirestoreLogger {
public:
    /**
     * @brief Initializes the logger with an API key for Firestore.
     * @param apiKey The API key used for authenticating Firestore API requests.
     */
    static void Initialize(const std::string &apiKey);

    /**
     * @brief Logs a message with a specified level to Firestore.
     * @param level The severity level of the log (e.g., "INFO", "WARNING", "ERROR").
     * @param message The message to log.
     */
    static void Log(const std::string &level, const std::string &message);

private:
    /**
     * @brief Generates a timestamp string in ISO 8601 format.
     * @return A string representing the current time formatted as ISO 8601.
     */
    static std::string GenerateTimestamp();

    static std::string apiKey; ///< API key for Firestore access.
    static inline std::string baseUrl = "https://firestore.googleapis.com/v1/projects/traffic-light-control-uofg/databases/(default)/documents/logs"; ///< Base URL for Firestore logging.
};

#endif // FIRESTORELOGGER_H
