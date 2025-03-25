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
void Renderer::addDrawable(std::vector<std::shared_ptr<sf::Vertex>> vertices, sf::PrimitiveType primType) {
    prims.push_back(Prim(vertices, primType));
    std::cout << "?\n";
}

void Renderer::clearDrawables(){
    drawables.clear();
}

void Renderer::drawFrame(){
        // Clear window
        Renderer::renderWindow.clear(sf::Color::Black);

        // Draw drawables
        for(const auto& drawable : drawables){
            renderWindow.draw(*drawable);
        }

        // Draw primitives
        for(const auto& primitive : prims){
            std::vector<sf::Vertex> rawVerts;
            rawVerts.reserve(primitive.verts.size());
            
            for(const auto& vertexPtr : primitive.verts) {
                if (vertexPtr) {
                    rawVerts.push_back(*vertexPtr);
                }
            }

            renderWindow.draw(rawVerts.data(), rawVerts.size(), primitive.primType);
        }

        // End render frame
        renderWindow.display();

        // Clear drawables
        drawables.clear();
}
