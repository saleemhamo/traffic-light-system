//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CROSSGUARD_CARSTRAFFICLIGHTCOMPONENT_H
#define CROSSGUARD_CARSTRAFFICLIGHTCOMPONENT_H

class CarsTrafficLightComponent {
public:
    // Enum to represent the various states of the traffic control system
    enum class State {
        GREEN,
        RED,
        OFF
    };

    CarsTrafficLightComponent();

    void run();

    void update();

    static State getCurrentState();


private:
    State currentState; // Current state of the traffic control system
    State defaultState = CarsTrafficLightComponent::State::GREEN;

    void initializeState();

    // Private method to change the state of the system
    void changeState(State newState);

    // Private method to update the outputs (lights, buzzer) based on the current state
    void updateOutputs();
};

#endif //CROSSGUARD_CARSTRAFFICLIGHTCOMPONENT_H
