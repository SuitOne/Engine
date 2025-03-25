#pragma once

#include <sfml_includes.hpp>
#include <memory>

class Renderer{
    struct Prim {
        const std::vector<std::shared_ptr<sf::Vertex>> verts;
        const sf::PrimitiveType primType;

        Prim(std::vector<std::shared_ptr<sf::Vertex>> verts, sf::PrimitiveType primType) 
        : verts(verts), primType(primType) {}
    };

    private:
        sf::RenderWindow& renderWindow;
        std::vector<std::shared_ptr<sf::Drawable>> drawables;
        std::vector<Prim> prims;

    public:
        Renderer(sf::RenderWindow& renderWindow);

        void addDrawable(std::shared_ptr<sf::Drawable> drawable);
        void addDrawable(std::vector<std::shared_ptr<sf::Vertex>> vertices, sf::PrimitiveType primType);
        void clearDrawables();
        void drawFrame();
};
