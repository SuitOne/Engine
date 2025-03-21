#include "engine/input.hpp"
#include <iostream>

Input::Input(bool debugMode) : debugMode(debugMode){}

void Input::resetInput(){
    for (auto& [code, keycode] : keycodes) {
        keycode.wasPressedThisFrame = false;
        keycode.wasReleasedThisFrame = false;
    }
}

void Input::parseInput(const sf::Keyboard::Scancode& code, bool pressed){
    if(!keycodes.contains(code)){
        keycodes.insert({code, KeyCode()});
    }

    keycodes[code].isPressed = pressed;
    keycodes[code].wasPressedThisFrame = pressed;
    keycodes[code].wasReleasedThisFrame = !pressed;
}

bool Input::getKey(const sf::Keyboard::Scancode& code) {

    if(!keycodes.contains(code)){
        keycodes.insert({code, KeyCode()});
    }
    
    return keycodes[code].isPressed;
}

bool Input::getKeyDown(const sf::Keyboard::Scancode& code) {
    if(!keycodes.contains(code)){
        keycodes.insert({code, KeyCode()});
    }

    return keycodes[code].wasPressedThisFrame;
}

bool Input::getKeyUp(const sf::Keyboard::Scancode& code) {
    if(!keycodes.contains(code)){
        keycodes.insert({code, KeyCode()});
    }

    return keycodes[code].wasReleasedThisFrame;
}