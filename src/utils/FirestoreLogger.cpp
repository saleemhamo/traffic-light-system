#include "utils/FirestoreLogger.h"

std::string FirestoreLogger::apiKey = "";

void FirestoreLogger::Initialize(const std::string &apiKeyParam) {
    apiKey = apiKeyParam;
}

void FirestoreLogger::Log(const std::string &level, const std::string &message) {
    if (apiKey.empty()) {
        std::cerr << "FirestoreLogger not initialized with API key." << std::endl;
        return;
    }

    std::string logMessage = message;
    std::string logLevel = level; // The new log level parameter
    std::string timestamp = GenerateTimestamp();
    std::string fullUrl = baseUrl + "?key=" + apiKey; // Make sure to append the API key here

    std::ostringstream dataStream;
    dataStream << R"({ "fields": { "log": { "stringValue": ")" << logMessage
               << R"(" }, "level": { "stringValue": ")" << logLevel
               << R"(" }, "timestamp": { "stringValue": ")" << timestamp << R"(" } } })";

    std::string data = dataStream.str();

    auto response = cpr::Post(cpr::Url{fullUrl},
                              cpr::Header{{"Content-Type", "application/json"}},
                              cpr::Body{data});
}

std::string FirestoreLogger::GenerateTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%FT%T%z"); // Adjust the format if needed
    return ss.str();
}

std::string FirestoreLogger::GetApiKey()
{
    return apiKey;
}

std::string FirestoreLogger::GetBaseUrl()
{
    return baseUrl;
}