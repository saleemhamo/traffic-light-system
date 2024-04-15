#include <gtest/gtest.h>
#include "FirestoreLogger.h"

class FirestoreLoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize FirestoreLogger with a dummy API key before each test
        FirestoreLogger::Initialize("test-api-key");
    }

    void TearDown() override {
        // Clean up after each test if necessary
    }
};

TEST_F(FirestoreLoggerTest, Initialization) {
    // Test initialization (you might need to adjust based on accessible internal state or methods)
    ASSERT_FALSE(FirestoreLogger::GetApiKey().empty());
}

TEST_F(FirestoreLoggerTest, LogMessage) {
    // Test that logging does not throw and is formatted correctly
    // This requires that you can inspect some result of FirestoreLogger::Log
    // In reality, you'd need a mock or some way to observe the logging output
    ASSERT_NO_THROW(FirestoreLogger::Log("INFO", "This is a test log message"));
}

TEST_F(FirestoreLoggerTest, HandleNoApiKey) {
    // Directly modify the API key to simulate an uninitialized state
    FirestoreLogger::Initialize("");
    ASSERT_THROW(FirestoreLogger::Log("ERROR", "No API key set"), std::runtime_error);
}
