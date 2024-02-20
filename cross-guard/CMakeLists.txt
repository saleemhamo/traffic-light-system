cmake_minimum_required(VERSION 3.27)
project(CrossGuard)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(
        _cross_guard src/main3.cpp
        src/actuators/TrafficLight.h
        src/actuators/PedestrianLight.h
        src/actuators/WarningSystem.h
        src/communication/ProtocolHandler.h
        src/control_logic/StateTransitionLogic.h
        src/control_logic/StateTransitionLogic.cpp
        src/control_logic/TrafficControlSystem.h
        src/control_logic/TrafficControlSystem.cpp
        src/models/PedestrianEvent.h
        src/models/TrafficState.h
        src/sensors/CameraSensor.cpp
        src/sensors/CameraSensor.h
        src/utils/ErrorHandler.h
        src/utils/Logger.h
        src/control_logic/CarsTrafficLightComponent.h
        src/control_logic/CarsTrafficLightComponent.cpp
        src/main.cpp
)


add_executable(GoogleTests tests/logic_tests/TrafficControlSystem_test.cpp src/control_logic/TrafficControlSystem.cpp)


# Link GoogleTest to the test executable
target_link_libraries(GoogleTests ${GTEST_LIBRARIES} pthread)

