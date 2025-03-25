#pragma once
#include "engine/component.hpp"
#include "sfml_includes.hpp"

class Engine;

class View : public Component {
    public:
        void init() override;
        void tick() override;
    
    private:
        sf::View mainView;
        Engine* engine;
};
