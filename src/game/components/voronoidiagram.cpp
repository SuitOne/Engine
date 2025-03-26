#include "game/components/voronoidiagram.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include <random>
#include <memory>

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;
using boost::polygon::point_data;

VoronoiDiagram::VoronoiDiagram(Engine& engineRef) : engine(engineRef){}

void VoronoiDiagram::init(){
    generate(generatePoints(50, 2000));
}

void VoronoiDiagram::tick(){
    timer += engine.deltaTime.asSeconds();

    if(timer >= 2){
        generate(generatePoints(100, 2000));
        timer = 0;
    }

    draw();
}

void VoronoiDiagram::generate(const std::vector<sf::Vector2f>& points){
    inputPoints = points;

    std::vector<point_data<double>> boostPoints;
    for(const auto& p : points) {
        boostPoints.emplace_back(p.x, p.y);
    } 
    
    vd.clear();

    construct_voronoi(boostPoints.begin(), boostPoints.end(), &vd);
}

void VoronoiDiagram::draw() const{
    // Forward input points to renderer
    for (const auto& p : inputPoints) {
        sf::CircleShape shape(3.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({p.x - 3.0f, p.y - 3.0f});

        engine.eRenderer->addRenderCommand(std::make_shared<sf::CircleShape>(shape));
    }

    for(const auto& cell : vd.cells()){
        drawCell(cell);
    }
}

void VoronoiDiagram::drawCell(const boost::polygon::voronoi_cell<double>& cell) const{
    // Create vector for vertex storage
    std::vector<const boost::polygon::voronoi_vertex<double>*> vertVect {};
    std::vector<std::shared_ptr<sf::Vertex>> vectorVector {};

    // Get site point of cell
    std::size_t index = cell.source_index();
    auto point = inputPoints[index];

    // Push back the site point
    vectorVector.push_back(std::make_shared<sf::Vertex>(point));

    // Get first cell edge
    const boost::polygon::voronoi_edge<double>* edge = 
        cell.incident_edge();

    // Loop over all cell edges
    do {
        // Draw the edge
        drawEdge(*edge);
        
        // Add vertices to vector
        vertVect.push_back(edge->vertex0());
        vertVect.push_back(edge->vertex1());

        // Move to next edge
        edge = edge->next();
    } while (edge != cell.incident_edge());

    // Convert collected vertices to sf vectors
    for(const auto& vert : vertVect){
        if(vert != nullptr){
            sf::Vector2f newVect = sf::Vector2f(static_cast<float>(vert->x()), static_cast<float>(vert->y()));
            sf::Vertex newVert = sf::Vertex(newVect, sf::Color::Blue);
            vectorVector.push_back(std::make_shared<sf::Vertex>(newVert));
        }
        
    }

    // Create primitive
    engine.eRenderer->addRenderCommand(vectorVector, sf::PrimitiveType::TriangleFan);
}

void VoronoiDiagram::drawEdge(const boost::polygon::voronoi_edge<double>& edge) const{
    if (edge.is_infinite()) return;

    auto v0 = edge.vertex0();
    auto v1 = edge.vertex1();

    std::vector<std::shared_ptr<sf::Vertex>> line{};
    
    sf::Vertex vert1 = sf::Vertex(
        sf::Vector2f(static_cast<float>(v0->x()), static_cast<float>(v0->y())), sf::Color::White);
    sf::Vertex vert2 = sf::Vertex(
        sf::Vector2f(static_cast<float>(v1->x()), static_cast<float>(v1->y())), sf::Color::White);

    line.push_back(std::make_shared<sf::Vertex>(vert1));
    line.push_back(std::make_shared<sf::Vertex>(vert2));

    engine.eRenderer->addRenderCommand(line, sf::PrimitiveType::Lines);
}

std::vector<sf::Vector2f> VoronoiDiagram::generatePoints(int amount, int range){
    // Generate random points
    std::vector<sf::Vector2f> points;
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;

    for(int i = 0; i < amount; ++i){
        points.emplace_back(distX(gen) * range, distY(gen) * range);
    }

    return points;
}
