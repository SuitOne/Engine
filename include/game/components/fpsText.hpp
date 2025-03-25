#pragma once
#include "engine/component.hpp"
#include "sfml_includes.hpp"

class Engine;

class FPSText : public Component {
    public:
        FPSText(std::shared_ptr<sf::Font> debugFont);

        void init() override;
        void tick() override;

    private:
        sf::Text text;
        Engine* pEngine;
};
