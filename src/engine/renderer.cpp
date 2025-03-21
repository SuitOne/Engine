#include "engine/renderer.hpp"
#include "engine/engine.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

Renderer::Renderer(sf::RenderWindow& renderWindow)
    : renderWindow(renderWindow){}

void Renderer::addDrawable(std::shared_ptr<sf::Drawable> drawable){
    drawables.push_back(drawable);
}

void Renderer::clearDrawables(){
    drawables.clear();
}

void Renderer::drawFrame(){
        // Clear window
        Renderer::renderWindow.clear(sf::Color::Black);

        // Draw
        for(const auto& drawable : drawables){
            renderWindow.draw(*drawable);
        }

        // End render frame
        renderWindow.display();

        // Clear drawables
        drawables.clear();
}
