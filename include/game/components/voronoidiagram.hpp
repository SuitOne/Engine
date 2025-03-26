#pragma once
#include <vector>
#include "sfml_includes.hpp"
#include "engine/component.hpp"

// Disable the C5055 warning
#pragma warning(push)
#pragma warning(disable: 5055)
#pragma warning(disable: 4244)

#include "boost/polygon/voronoi.hpp"

// Restore the previous warning state
#pragma warning(pop)

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
        void drawEdge(const boost::polygon::voronoi_edge<double>& edge) const;
        void drawCell(const boost::polygon::voronoi_cell<double>& cell) const;

        std::vector<sf::Vector2f> generatePoints(int amount, int range);
};
