//
// Created by Saleem Hamo on 07/02/2024.
//

#ifndef CROSSGUARD_LOGGER
#define CROSSGUARD_LOGGER

#include <fstream>
#include <string>
#include <ctime>
#include "FirestoreLogger.h"

class Logger {
public:
    static const std::string defaultFileName;

    static void init(const std::string &filename = defaultFileName);

    static void logInfo(const std::string &message);

    static void logError(const std::string &message);

    static void close();

private:
    static std::ofstream logFile;

    static void log(const std::string &level, const std::string &message);
};

#endif //CROSSGUARD_LOGGER
