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
    generate(generatePoints(200, 2000));
}

void VoronoiDiagram::tick(){
    timer += engine.deltaTime.asSeconds();

    if(timer >= 2){
        generate(generatePoints(200, 2000));
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
    // Ignore for now, mainly for debugging cell position
    // for (const auto& p : inputPoints) {
    //     sf::CircleShape shape(3.0f);
    //     shape.setFillColor(sf::Color::Red);
    //     shape.setPosition({p.x - 3.0f, p.y - 3.0f});

    //     engine.eRenderer->addRenderCommand(std::make_shared<sf::CircleShape>(shape), 101);
    // }

    // Draw cells
    for(const auto& cell : vd.cells()){
        drawCell(cell);
    }

    // Draw bounding box
    sf::Vector2f tRight {boundingBox.x, boundingBox.y};
    sf::Vector2f bRight {boundingBox.x, -boundingBox.y};
    sf::Vector2f bLeft {-boundingBox.x, -boundingBox.y};
    sf::Vector2f tLeft {-boundingBox.x, boundingBox.y};

    drawEdge(tLeft, tRight, sf::Color::Red);
    drawEdge(tRight, bRight, sf::Color::Red);
    drawEdge(bRight, bLeft, sf::Color::Red);
    drawEdge(bLeft, tLeft, sf::Color::Red);

    // Draw background
    sf::RectangleShape backdrop;
    backdrop.setSize(sf::Vector2f(boundingBox.x * 2, boundingBox.y * 2));
    backdrop.setPosition(sf::Vector2f(-boundingBox.x, -boundingBox.y));
    backdrop.setFillColor(sf::Color::Blue);
    engine.eRenderer->addRenderCommand(std::make_shared<sf::RectangleShape>(backdrop), 90);
}

void VoronoiDiagram::drawCell(const boost::polygon::voronoi_cell<double>& cell) const{
    // Create vector for edge, vertex and vector storage
    std::vector<const boost::polygon::voronoi_edge<double>*> edges {};
    std::vector<const boost::polygon::voronoi_vertex<double>*> cellVertices {};
    std::vector<std::shared_ptr<sf::Vertex>> fanVertices {};

    // Get site point of cell
    std::size_t index = cell.source_index();
    auto point = inputPoints[index];

    // Push back the site point
    fanVertices.push_back(std::make_shared<sf::Vertex>(point, sf::Color(20, 125, 20)));

    // Get first cell edge
    const boost::polygon::voronoi_edge<double>* edge = 
        cell.incident_edge();

    // Collect all valid edges and vertices
    do {
        // Abort cell if infinite edges
        if(edge->is_infinite()) return;

        // Store vertices, abort if outside bounds
        auto vert0 = edge->vertex0();
        auto vert1 = edge->vertex1();

        // Greater check
        if(vert0->x() > boundingBox.x ||
         vert0->y() > boundingBox.y ||
         vert1->x() > boundingBox.x ||
         vert1->y() > boundingBox.y) return;

        // Lesser check
        if(vert0->x() < -boundingBox.x ||
         vert0->y() < -boundingBox.y ||
         vert1->x() < -boundingBox.x ||
         vert1->y() < -boundingBox.y) return;

        // Push back edge
        edges.push_back(edge);
        
        // Add vertices to vector
        cellVertices.push_back(edge->vertex0());
        cellVertices.push_back(edge->vertex1());

        // Move to next edge
        edge = edge->next();
    } while (edge != cell.incident_edge());

    // Calculate the distance of the point from the center
    sf::Vector2f center(0, 0);
    double distance = std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2));
    double maxDistance = std::sqrt(2 * std::pow(boundingBox.x / 2.0f, 2));

    // Determine cell color based on distance
    sf::Color cellColor;

    if (distance < maxDistance / 3) {
        // Closer to the center
        cellColor = sf::Color(50, 50, 50);
        fanVertices.front()->color = sf::Color(150, 150, 150);
    } else if (distance < 2.75f * maxDistance / 3) {
        // Middle
        cellColor = sf::Color(50, 120, 50);
        fanVertices.front()->color = sf::Color(70, 140, 70);
    } else {
        // Closer to the edge
        cellColor = sf::Color(210, 180, 140);
        fanVertices.front()->color = sf::Color(230, 210, 160);
    }

    // Convert collected vertices to sf vectors
    for(const auto& vert : cellVertices){
        if(vert != nullptr){
            sf::Vector2f newVect = sf::Vector2f(static_cast<float>(vert->x()), static_cast<float>(vert->y()));
            sf::Vertex newVert = sf::Vertex(newVect, cellColor);
            fanVertices.push_back(std::make_shared<sf::Vertex>(newVert));
        }
    }

    // Draw edges
    for(const auto& edge : edges){
        drawEdge(*edge);
    }

    // Draw the cell
    engine.eRenderer->addRenderCommand(fanVertices, sf::PrimitiveType::TriangleFan);
}

void VoronoiDiagram::drawEdge(const boost::polygon::voronoi_edge<double>& edge, const sf::Color& color) const{
    if (edge.is_infinite()) return;

    auto v0 = edge.vertex0();
    auto v1 = edge.vertex1();

    std::vector<std::shared_ptr<sf::Vertex>> line{};
    
    sf::Vertex vert1 = sf::Vertex(
        sf::Vector2f(static_cast<float>(v0->x()), static_cast<float>(v0->y())), color);
    sf::Vertex vert2 = sf::Vertex(
        sf::Vector2f(static_cast<float>(v1->x()), static_cast<float>(v1->y())), color);

    line.push_back(std::make_shared<sf::Vertex>(vert1));
    line.push_back(std::make_shared<sf::Vertex>(vert2));

    engine.eRenderer->addRenderCommand(line, sf::PrimitiveType::Lines, 101);
}

void VoronoiDiagram::drawEdge(const sf::Vector2f& v0, const sf::Vector2f& v1, const sf::Color& color) const{
    std::vector<std::shared_ptr<sf::Vertex>> line{};
    
    sf::Vertex vert1 = sf::Vertex(
        v0, color);
    sf::Vertex vert2 = sf::Vertex(
        v1, color);

    line.push_back(std::make_shared<sf::Vertex>(vert1));
    line.push_back(std::make_shared<sf::Vertex>(vert2));

    engine.eRenderer->addRenderCommand(line, sf::PrimitiveType::Lines, 101);
}

std::vector<sf::Vector2f> VoronoiDiagram::generatePoints(int amount, float range){
    // Set bounding box
    boundingBox = sf::Vector2f(range / 2.f, range / 2.f);

    // Generate random points
    std::vector<sf::Vector2f> points;
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distX;
    std::uniform_real_distribution<float> distY;

    for(int i = 0; i < amount; ++i){
        points.emplace_back(distX(gen) * range - range / 2.f, distY(gen) * range - range / 2.f);
    }

    return points;
}
