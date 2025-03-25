#pragma once
#include "engine/scene.hpp"

class sMainMenu : public Scene{
    public:
        sMainMenu(Engine& engine);
        void tick() override;
};
