cmake_minimum_required(VERSION 3.10)
project(CrossGuard)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the main executable
add_executable(CrossGuard
        src/main.cpp
        src/wiringPiStub.cpp # Stub file
        src/utils/Logger.cpp
        src/actuators/LED.cpp
        src/actuators/Buzzer.cpp
        # src/sensors/CameraSensor.cpp
        # src/sensors/UltrasonicSensor.cpp
        src/models/TrafficLight.cpp
        src/main/cars_traffic_light_system/CarsTrafficLightSystem.cpp
        src/main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.cpp
        src/main/warning_system/WarningSystem.cpp
        src/main/checking_system/CheckingSystem.cpp
        src/main/MainSystem.cpp
)

# Conditional linking with the wiringPi library
if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    target_link_libraries(CrossGuard wiringPi)
endif ()

####### Testing Configuration #######

# Enable CTest
enable_testing()

# Find Boost and use its unit test framework if available
find_package(Boost COMPONENTS unit_test_framework)

if (Boost_FOUND)
    message(STATUS "Boost found, enabling tests.")
    include_directories(${Boost_INCLUDE_DIRS})

    # Conditional test paths based on whether the environment is Raspberry Pi
    if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
        message(STATUS "Configuring tests for Raspberry Pi environment.")
        # Replace 'RPiBuzzerTest' with the target name for your test
        # Replace 'rpi_specific_tests_dir/Buzzer_test.cpp' with the correct file path
        add_executable(RPiBuzzerTest rpi_specific_tests_dir/Buzzer_test.cpp)
        target_link_libraries(RPiBuzzerTest ${Boost_LIBRARIES})
        add_test(NAME RPiBuzzerUnitTest COMMAND RPiBuzzerTest)
    else ()
        message(STATUS "Configuring tests for non-Raspberry Pi environment.")
        # Replace 'BuzzerTest' with the target name for your test
        # Provide the correct path to Buzzer_test.cpp
        add_executable(BuzzerTest tests/hardware_tests/actuators/Buzzer_test.cpp)
        target_link_libraries(BuzzerTest ${Boost_LIBRARIES})
        add_test(NAME BuzzerUnitTest COMMAND BuzzerTest)
    endif ()
else ()
    message(STATUS "Boost not found, tests will not be available.")
endif ()