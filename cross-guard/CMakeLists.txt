cmake_minimum_required(VERSION 3.27)
project(_cross_guard)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        _cross_guard src/main.cpp
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
)
