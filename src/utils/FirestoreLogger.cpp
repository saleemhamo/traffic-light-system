#include "utils/FirestoreLogger.h"

std::string FirestoreLogger::apiKey = "";

void FirestoreLogger::Initialize(const std::string &apiKeyParam) {
    apiKey = apiKeyParam;
}

void FirestoreLogger::Log(const std::string &message) {
    if (apiKey.empty()) {
        std::cerr << "FirestoreLogger not initialized with API key." << std::endl;
        return;
    }

    std::string logMessage = message;
    std::string timestamp = GenerateTimestamp();
    std::string fullUrl = baseUrl;


    std::ostringstream dataStream;
    dataStream << R"({ "fields": { "log": { "stringValue": ")" << logMessage
               << R"(" }, "timestamp": { "stringValue": ")" << timestamp << R"(" } } })";

    std::string data = dataStream.str();

    auto response = cpr::Post(cpr::Url{fullUrl},
                              cpr::Header{{"Content-Type", "application/json"}},
                              cpr::Body{data});

    std::cout << response.text << std::endl;
}

std::string FirestoreLogger::GenerateTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%FT%T%z"); // Adjust the format if needed
    return ss.str();
}
