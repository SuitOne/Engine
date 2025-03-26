#pragma once
#include "engine/component.hpp"
#include "sfml_includes.hpp"

class Engine;

class DebugOverlay : public Component {
    public:
        DebugOverlay(std::shared_ptr<sf::Font> debugFont);

        void init() override;
        void tick() override;

    private:
        sf::Text fpsText;
        sf::RectangleShape backdrop;
        Engine* pEngine;
        bool enabled {false};
};
