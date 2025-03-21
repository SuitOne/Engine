#pragma once

#include "sfml_includes.hpp"
#include "engine/component.hpp"
#include <memory>

class Sprite : public Component {
    public:
        Sprite(std::weak_ptr<Entity> owner, std::shared_ptr<sf::Drawable> drawable);
        void init() override;
        void tick() override;

    protected:
        std::shared_ptr<sf::Drawable> drawable;
};