#ifndef FIRESTORELOGGER_H
#define FIRESTORELOGGER_H

#include <string>
#include <cpr/cpr.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

class FirestoreLogger {
public:
    static void Initialize(const std::string& apiKey);
    static void Log(const std::string& message);

private:
    static std::string GenerateTimestamp();
    static std::string apiKey;
    static inline std::string baseUrl = "https://firestore.googleapis.com/v1/projects/traffic-light-control-uofg/databases/(default)/documents/logs";
};

#endif // FIRESTORELOGGER_H
