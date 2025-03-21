#pragma once
#include "engine/scene.hpp"

class sMainTest : public Scene{
    public:
        sMainTest(Engine& engine);
        void tick() override;

    private:
        std::shared_ptr<sf::CircleShape> player{nullptr};
};