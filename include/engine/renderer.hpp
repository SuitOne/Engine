#pragma once

#include <sfml_includes.hpp>
#include <memory>

class Renderer{
    private:
        sf::RenderWindow& renderWindow;
        std::vector<std::shared_ptr<sf::Drawable>> drawables;

    public:
        Renderer(sf::RenderWindow& renderWindow);

        void addDrawable(std::shared_ptr<sf::Drawable> drawable);
        void clearDrawables();
        void drawFrame();
};