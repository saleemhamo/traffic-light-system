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
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Check if the processor is ARM (common in Raspberry Pi)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
        target_link_libraries(CrossGuard wiringPi)
    endif()
endif()

# Uncomment below to add Google Test (if you have tests)
#enable_testing()
#add_subdirectory(tests/hardware_tests/actuators)


#cmake_minimum_required(VERSION 3.27)
#project(CrossGuard)
#
## Set C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED True)
#
## Source and header files
#set(SOURCE_FILES
##        src/control_logic/TrafficControlSystem.cpp
##        src/models/TrafficLight.cpp
##        src/main/warning_system/WarningSystem.cpp
##        src/main/checking_system/CheckingSystem.cpp
##        src/main/cars_traffic_light_system/CarsTrafficLightSystem.cpp
##        src/main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.cpp
##        src/main/MainSystem.cpp
#        src/actuators/LED.cpp
##        src/actuators/Buzzer.cpp
##        src/sensors/UltrasonicSensor.cpp
#        src/main.cpp # Main must be included
#)
#
#set(HEADER_FILES
#        src/wiringPiStub.h
#        src/actuators/LED.h
##        src/actuators/Buzzer.h
##        src/control_logic/TrafficControlSystem.h
##        src/utils/ErrorHandler.h
##        src/utils/Logger.h
##        src/models/TrafficLight.h
##        src/main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.h
##        src/main/cars_traffic_light_system/CarsTrafficLightSystem.h
##        src/main/warning_system/WarningSystem.h
##        src/main/checking_system/CheckingSystem.h
##        src/main/SystemInterface.h
##        src/main/MainSystem.h
##        src/utils/Constants.h
##        src/sensors/UltrasonicSensor.h
##        src/sensors/CameraSensor.h
#)
#
## Add the executable for the main application
#add_executable(CrossGuard ${SOURCE_FILES} ${HEADER_FILES})
#
## Uncomment these lines if you want to include Google Test
## find_package(GTest REQUIRED)
## include_directories(${GTEST_INCLUDE_DIRS})
#
## Test files
## set(TEST_FILES
##     tests/hardware_tests/actuators/LED_test.cpp
##     tests/hardware_tests/actuators/Buzzer_test.cpp
## )
#
## Uncomment to add the executable for Google Test based tests
## add_executable(GoogleTests ${TEST_FILES} ${SOURCE_FILES})
## Exclude main.cpp from test build if it contains the main function of your application
## target_link_libraries(GoogleTests ${GTEST_LIBRARIES} pthread)
