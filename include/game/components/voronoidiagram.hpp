#pragma once
#include <vector>
#include "boost/polygon/voronoi.hpp"
#include "sfml_includes.hpp"
#include "engine/component.hpp"

class Engine;

class VoronoiDiagram : public Component {
    public:
        VoronoiDiagram(Engine& engineRef);

        void generate(const std::vector<sf::Vector2f>& points);

        void init() override;
        void tick() override;

    private:
        boost::polygon::voronoi_diagram<double> vd;
        std::vector<sf::Vector2f> inputPoints;
        float timer {0};
        Engine& engine;

        void draw() const;
        void drawEdge(const boost::polygon::voronoi_edge<double> edge) const;

        std::vector<sf::Vector2f> generatePoints(int amount);
};
