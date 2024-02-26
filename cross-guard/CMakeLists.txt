cmake_minimum_required(VERSION 3.27)
project(CrossGuard)

set(CMAKE_CXX_STANDARD 17)

# Locate GTest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable(CrossGuard
        src/actuators/Buzzer.h
        src/actuators/LED.h
        src/control_logic/TrafficControlSystem.h
        src/control_logic/TrafficControlSystem.cpp
        src/utils/ErrorHandler.h
        src/utils/Logger.h
        src/models/TrafficLight.cpp
        src/models/TrafficLight.h
        src/main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.h
        src/main/cars_traffic_light_system/CarsTrafficLightSystem.h
        src/main/warning_system/WarningSystem.cpp
        src/main/warning_system/WarningSystem.h
        src/main/checking_system/CheckingSystem.cpp
        src/main.cpp
        src/actuators/LED.cpp
        src/main/SystemInterface.h
        src/main/cars_traffic_light_system/CarsTrafficLightSystem.cpp
        src/main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.cpp
        src/actuators/Buzzer.cpp
        src/sensors/UltrasonicSensor.h
        src/sensors/CameraSensor.h
        src/main/checking_system/CheckingSystem.h
        src/main/MainSystem.h
        src/main/MainSystem.cpp
        src/utils/Constants.h
        tests/hardware_tests/actuators/LED_test.cpp
        tests/hardware_tests/actuators/Buzzer_test.cpp
        src/sensors/UltrasonicSensor.cpp
)


#add_executable(GoogleTests tests/logic_tests/TrafficControlSystem_test.cpp src/control_logic/TrafficControlSystem.cpp)


# Link GoogleTest to the test executable
#target_link_libraries(GoogleTests ${GTEST_LIBRARIES} pthread)

