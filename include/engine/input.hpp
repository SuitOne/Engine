#pragma once
#include <map>
#include "sfml_includes.hpp"

struct KeyCode{
    bool wasPressedThisFrame{false};
    bool wasReleasedThisFrame{false};
    bool isPressed{false};
};

class Input{
    public:
        Input(bool debugMode);
        void init(bool debugMode);
        void resetInput();
        void parseInput(const sf::Keyboard::Scancode& code, bool pressed);
        bool getKeyDown(const sf::Keyboard::Scancode& code);
        bool getKeyUp(const sf::Keyboard::Scancode& code);
        bool getKey(const sf::Keyboard::Scancode& code);

        private:
        std::unordered_map<sf::Keyboard::Scancode, KeyCode> keycodes;
        bool debugMode;
};