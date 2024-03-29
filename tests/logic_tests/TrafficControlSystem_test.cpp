//
// Created by Saleem Hamo on 13/02/2024.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../src/control_logic/TrafficControlSystem.h"

TEST(TrafficControlSystemTest, InitialState) {
    TrafficControlSystem system;
    EXPECT_EQ(system.getCurrentState(), TrafficControlSystem::State::CAR_RED_PEDESTRIAN_GREEN);
}

TEST(TrafficControlSystemTest, TransitionToCarGreenPedestrianRed) {
    TrafficControlSystem system;
    system.handleCarTrafficLightChange(true); // Car light turns green
    system.update(); // Process the update
    EXPECT_EQ(system.getCurrentState(), TrafficControlSystem::State::CAR_GREEN_PEDESTRIAN_RED);
}

// TODO: Use mocking
//TEST(MyTestCase, TestSomething) {
//    MockDependency mockDependency;
//    EXPECT_CALL(mockDependency, MethodToBeMocked(testing::_))
//            .Times(1)
//            .WillOnce(testing::Return());
//
//    // Your test code here, which should call MethodToBeMocked at some point
//}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}