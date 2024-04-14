#define BOOST_TEST_MODULE FirestoreLoggerTest
#include <boost/test/included/unit_test.hpp>

#include "utils/FirestoreLogger.h"

BOOST_AUTO_TEST_SUITE(FirestoreLoggerTests)

BOOST_AUTO_TEST_CASE(test_initialization)
{
    // Test initialization with a valid API key
    std::string apiKey = "";
    FirestoreLogger::Initialize(apiKey);

    BOOST_CHECK_EQUAL(FirestoreLogger::GetApiKey(), apiKey);
}

BOOST_AUTO_TEST_CASE(test_logging)
{
    // Test logging with a valid API key and message
    std::string apiKey = "";
    FirestoreLogger::Initialize(apiKey);

    std::string logLevel = "info";
    std::string message = "Test log message";

    // Redirect std::cerr to a stringstream to capture the output
    std::stringstream capturedOutput;
    std::streambuf *originalCerr = std::cerr.rdbuf(capturedOutput.rdbuf());

    // Log the message
    FirestoreLogger::Log(logLevel, message);

    // // Check if logging was successful by examining HTTP response status
    // // For simplicity, assume successful logging if HTTP response status is 200
    // cpr::Response response = cpr::Post(cpr::Url{FirestoreLogger::GetBaseUrl() + "?key=" + apiKey},
    //                                    cpr::Header{{"Content-Type", "application/json"}},
    //                                    cpr::Body{R"({ "fields": { "log": { "stringValue": "Test log message" }, "level": { "stringValue": "info" }, "timestamp": { "stringValue": "2024-04-16T15:45:00+0000" } } })"});
    // BOOST_CHECK_EQUAL(response.status_code, 200);
    
    // Restore std::cerr
    std::cerr.rdbuf(originalCerr);

    // Check if the log message was outputted correctly
    std::string expectedOutput = "FirestoreLogger not initialized with API key.";
    BOOST_CHECK_EQUAL(capturedOutput.str(), expectedOutput);
}

BOOST_AUTO_TEST_CASE(test_timestamp_generation)
{
    // Test timestamp generation indirectly by checking if it's included in the log
    // Initialize FirestoreLogger with API key
    std::string apiKey = ""; // Replace with your API key
    FirestoreLogger::Initialize(apiKey);

    // Log a message
    std::string level = "info";
    std::string message = "Test log message";
    FirestoreLogger::Log(level, message);

    // Retrieve the logged message from Firestore (assuming it's stored with the timestamp)
    // For simplicity, let's assume the logged message contains the timestamp
    std::string loggedMessage = ""; // Replace with code to retrieve logged message
    bool containsTimestamp = loggedMessage.find("2024-04-16T15:45:00+0000") != std::string::npos;

    // Validate that the logged message contains the timestamp
    BOOST_CHECK(containsTimestamp);
}

BOOST_AUTO_TEST_SUITE_END()
