#include "engine/renderer.hpp"
#include "engine/engine.hpp"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

Renderer::Renderer(sf::RenderWindow& renderWindow)
    : renderWindow(renderWindow){}

void Renderer::addRenderCommand(std::shared_ptr<sf::Drawable> drawable, uint16_t layer){
    renderQueue.push_back(std::make_unique<RenderCommand>(RenderCommand(drawable, layer, currentOrder++)));
}
void Renderer::addRenderCommand(std::vector<std::shared_ptr<sf::Vertex>> vertices, sf::PrimitiveType primType, uint16_t layer) {
    std::shared_ptr<Prim> pPrim = std::make_shared<Prim>(Prim(vertices, primType));
    renderQueue.push_back(std::make_unique<RenderCommand>(RenderCommand(pPrim, layer, currentOrder++)));
}

void Renderer::clearRenderQueue(){
    renderQueue.clear();
}

void Renderer::drawFrame(){
        // Clear window
        Renderer::renderWindow.clear(sf::Color::Black);

        // Sort render queue
        std::sort(renderQueue.begin(), renderQueue.end(),
         [](const std::unique_ptr<RenderCommand>& a, const std::unique_ptr<RenderCommand>& b) {
            return *a < *b;
        });
        
        // Draw render commands from render queue
        for(const auto& renderCommand : renderQueue){
            if(renderCommand->drawable != nullptr){
                // Drawables
                renderWindow.draw(*renderCommand->drawable);
            } else if(renderCommand->prim != nullptr){
                // Primitives
                std::vector<sf::Vertex> rawVerts;
                rawVerts.reserve(renderCommand->prim->verts.size());
                
                for(const auto& vertexPtr : renderCommand->prim->verts) {
                    if (vertexPtr) {
                        rawVerts.push_back(*vertexPtr);
                    }
                }

                renderWindow.draw(rawVerts.data(), rawVerts.size(), renderCommand->prim->primType);
            } else {
                // Invalid, catch
                std::cerr << "Invalid RenderCommand passed to Renderer!" << std::endl;
            }
        }

        // End render frame
        renderWindow.display();

        // Clear drawables
        renderQueue.clear();
}

void Renderer::setMainView(sf::View& newMainView){
    renderWindow.setView(newMainView);
}
