//
// Created by Saleem Hamo on 20/02/2024.
//
#include "CarsTrafficLightComponent.h"

CarsTrafficLightComponent::CarsTrafficLightComponent() : currentState(State::GREEN) {

    updateOutputs();
}

// TODO: initialize a thread that acts as the normal cars traffic light
// Our system should read input from there and just send a signal to make it red when necessary (transition to CAR_RED_PEDESTRIAN_GREEN_SAFE)
void CarsTrafficLightComponent::run() {

}

CarsTrafficLightComponent::State CarsTrafficLightComponent::getCurrentState() {
    return CarsTrafficLightComponent::State::OFF;
}

void CarsTrafficLightComponent::update() {

}

void CarsTrafficLightComponent::initializeState() {

}

void CarsTrafficLightComponent::changeState(CarsTrafficLightComponent::State newState) {

}

void CarsTrafficLightComponent::updateOutputs() {

}

