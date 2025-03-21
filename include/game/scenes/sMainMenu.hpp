#pragma once
#include "engine/scene.hpp"

class sMainMenu : public Scene{
    public:
        sMainMenu(Engine& engine);
        void tick() override;

    private:
        std::shared_ptr<sf::Text> mainText;
};