#define BOOST_TEST_MODULE LoggerTest
#include <boost/test/included/unit_test.hpp>
#include "utils/Logger.h"
#include <fstream>
#include <chrono>
#include <thread>

BOOST_AUTO_TEST_SUITE(LoggerTests)

// Define a temporary log file name for testing
const std::string testLogFileName = "test.log";

BOOST_AUTO_TEST_CASE(test_initialization)
{
    // Initialize logger with the test log file name
    Logger::init(testLogFileName);

    // Check if the log file is successfully opened
    std::ifstream logFile(testLogFileName);
    BOOST_CHECK(logFile.is_open());

    // Close the log file
    logFile.close();

    // Close the logger
    Logger::close();
}

BOOST_AUTO_TEST_CASE(test_logging)
{
    // Initialize logger with the test log file name
    Logger::init(testLogFileName);

    // Log some messages
    Logger::logInfo("This is an informational message.");
    Logger::logError("This is an error message.");

    // Wait for a short time to ensure messages are written to the file
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Check if messages are written to the log file
    std::ifstream logFile(testLogFileName);
    std::string line;
    bool infoLogged = false;
    bool errorLogged = false;
    while (std::getline(logFile, line))
    {
        if (line.find("[INFO]") != std::string::npos && line.find("This is an informational message.") != std::string::npos)
            infoLogged = true;
        if (line.find("[ERROR]") != std::string::npos && line.find("This is an error message.") != std::string::npos)
            errorLogged = true;
    }
    BOOST_CHECK(infoLogged);
    BOOST_CHECK(errorLogged);

    // Close the log file
    logFile.close();

    // Close the logger
    Logger::close();
}

BOOST_AUTO_TEST_CASE(test_closing)
{
    // Initialize logger with the test log file name
    Logger::init(testLogFileName);

    // Close the logger
    Logger::close();

    // Check if the log file is closed
    std::ifstream logFile(testLogFileName);
    BOOST_CHECK(!logFile.is_open());
}

BOOST_AUTO_TEST_SUITE_END()
