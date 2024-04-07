cmake_minimum_required(VERSION 3.10)
project(CrossGuard)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include FetchContent module for downloading external content
include(FetchContent)

# Declare CPR as an external project
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG origin/master # It's better to lock this to a specific release version for consistency
)

# Make the fetched content available
FetchContent_MakeAvailable(cpr)

# Include directories
include_directories(include)

# Add the main executable
add_executable(CrossGuard
        src/main.cpp
        src/pigpio_stub.cpp # Stub file
        src/utils/Logger.cpp
        src/actuators/LED.cpp
        src/actuators/Buzzer.cpp
        # src/sensors/CameraSensor.cpp
        src/sensors/UltrasonicSensor.cpp
        src/sensors/PushButton.cpp
        src/models/TrafficLight.cpp
        src/main/CarsTrafficLightSystem.cpp
        src/main/PedestriansTrafficLightSystem.cpp
        src/main/WarningSystem.cpp
        src/main/CheckingSystem.cpp
        src/main/MainSystem.cpp
        src/utils/FirestoreLogger.cpp
)

# Prepare the list of libraries to link.
set(LINK_LIBS cpr::cpr)

# Conditionally append pigpio to the list if on an appropriate system.
if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    list(APPEND LINK_LIBS pigpio)
endif ()

# Link the libraries to the target.
target_link_libraries(CrossGuard PRIVATE ${LINK_LIBS})

####### Testing Configuration #######


# Find Boost and use its unit test framework if available
find_package(Boost COMPONENTS unit_test_framework QUIET)

if (NOT Boost_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            boost
            URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.bz2
    )
    FetchContent_MakeAvailable(boost)
    # Adjust the include path as needed based on how Boost is structured when fetched
endif ()

####### Testing Configuration #######

# Enable CTest for organizing tests
enable_testing()

# Check for Boost, now assumed to be available either locally or fetched
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

function(add_hardware_test TEST_NAME TEST_FILE)
    file(GLOB_RECURSE ACTUATORS_SOURCES "src/actuators/*.cpp")
    file(GLOB_RECURSE MAIN_SOURCES "src/main/*.cpp")
    file(GLOB_RECURSE MODELS_SOURCES "src/models/*.cpp")
    file(GLOB_RECURSE SENSORS_SOURCES "src/sensors/*.cpp")
    file(GLOB_RECURSE UTILS_SOURCES "src/utils/*.cpp")

    set(SOURCES
            ${ACTUATORS_SOURCES}
            ${MAIN_SOURCES}
            ${MODELS_SOURCES}
            ${SENSORS_SOURCES}
            ${UTILS_SOURCES}
    )

    # Define the executable for the test
    add_executable(${TEST_NAME}
            ${TEST_FILE}
            src/pigpio_stub.cpp # Stub file
            ${SOURCES}
    )

    # Link the necessary libraries
    target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} cpr::cpr)

    # Add the test to CTest
    add_test(NAME ${TEST_NAME}UnitTest COMMAND ${TEST_NAME})
endfunction(add_hardware_test)


# Assuming the Timer class is part of the 'utils' group of files
set(TIMER_SOURCES include/utils/Timer.h) # Adjust path as necessary

# Define a function for non-hardware tests if not already existing
function(add_unit_test TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE} ${TIMER_SOURCES})
    target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES} cpr::cpr) # Add other dependencies as needed
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction(add_unit_test)

# Conditional test paths
if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    message(STATUS "Configuring tests for Raspberry Pi environment.")
    add_executable(RPiExampleTest tests/RPiExampleTest.cpp)
    target_link_libraries(RPiExampleTest ${Boost_LIBRARIES} ${LINK_LIBS})
    add_test(NAME RPiExampleUnitTest COMMAND RPiExampleTest)
else ()
    message(STATUS "Configuring tests for non-Raspberry Pi environment.")
    include_directories(${CMAKE_SOURCE_DIR}/include)

    add_hardware_test(BuzzerTest "tests/hardware_tests/actuators/Buzzer_test.cpp")
    add_hardware_test(LEDTest "tests/hardware_tests/actuators/LED_test.cpp")
#    add_hardware_test(UltrasonicSensorTest "tests/hardware_tests/sensors/Ultrasonic_test.cpp")
    # add_hardware_test(CameraSensorTest "tests/hardware_tests/sensors/Camera_test.cpp")
    
    # Ideas of tests to be implemented
    # add_hardware_test(PushButtonTest "tests/hardware_tests/sensors/PushButton_test.cpp")
    # add_hardware_test(TrafficLightTest "tests/hardware_tests/models/TrafficLight_test.cpp")
    # add_hardware_test(CarsTrafficLightSystemTest "tests/hardware_tests/main/CarsTrafficLightSystem_test.cpp")
    # add_hardware_test(PedestriansTrafficLightSystemTest "tests/hardware_tests/main/PedestriansTrafficLightSystem_test.cpp")
    # add_hardware_test(WarningSystemTest "tests/hardware_tests/main/WarningSystem_test.cpp")
    # add_hardware_test(CheckingSystemTest "tests/hardware_tests/main/CheckingSystem_test.cpp")
    # add_hardware_test(MainSystemTest "tests/hardware_tests/main/MainSystem_test.cpp")
    # add_hardware_test(FirestoreLoggerTest "tests/hardware_tests/utils/FirestoreLogger_test.cpp")
    # add_hardware_test(TimerTest "tests/hardware_tests/utils/Timer_test.cpp")

    add_unit_test(TimerTest "tests/TimerTest.cpp")

endif ()
