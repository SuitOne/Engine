#pragma once

#include <sfml_includes.hpp>
#include <memory>

class Renderer{
    /// @brief Internal struct used for creating primitives
    /// of many types and storing them in the render queue in a render command
    struct Prim {
        const std::vector<std::shared_ptr<sf::Vertex>> verts;
        const sf::PrimitiveType primType;

        Prim(std::vector<std::shared_ptr<sf::Vertex>> verts, sf::PrimitiveType primType) 
        : verts(verts), primType(primType) {}
    };

    /// @brief Internal struct used for taking in a variety of values that can 
    /// be constructed in public functions and then fed into the renderQueue for 
    /// a quick and sorted draw call
    struct RenderCommand {
        std::shared_ptr<sf::Drawable> drawable;
        std::shared_ptr<Prim> prim;

        uint16_t layer;
        std::size_t orderInFrame;

        RenderCommand(std::shared_ptr<sf::Drawable> drawable, uint16_t layer, std::size_t orderInFrame) :
            drawable(drawable), prim(nullptr), layer(layer), orderInFrame(orderInFrame){}

        RenderCommand(std::shared_ptr<Prim> prim, uint16_t layer, std::size_t orderInFrame) :
            drawable(nullptr), prim(prim), layer(layer), orderInFrame(orderInFrame){}

        bool operator<(const RenderCommand& other) const{
            return (layer < other.layer) || 
                    (layer == other.layer && orderInFrame < other.orderInFrame);
        }
    };

    private:
        sf::RenderWindow& renderWindow;
        std::vector<std::unique_ptr<RenderCommand>> renderQueue;
        std::vector<Prim> prims;
        std::size_t currentOrder {0};

    public:
        Renderer(sf::RenderWindow& renderWindow);

        void setMainView(sf::View& newMainView);
        void addRenderCommand(std::shared_ptr<sf::Drawable> drawable, uint16_t layer = 100);
        void addRenderCommand(std::vector<std::shared_ptr<sf::Vertex>> vertices, sf::PrimitiveType primType, uint16_t layer = 100);
        void clearRenderQueue();
        void drawFrame();
};
