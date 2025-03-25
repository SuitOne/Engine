#include "game/scenes/sMainTest.hpp"
#include "game/components/sprite.hpp"
#include "game/components/voronoidiagram.hpp"

#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/input.hpp"
#include "engine/entity.hpp"
#include <iostream>

sMainTest::sMainTest(Engine& engine) :
    Scene(engine) {

    // Create voronoi
    std::shared_ptr<Entity> voronoiEntity = createEntity();
    voronoiEntity->addComponent(std::make_shared<VoronoiDiagram>(engine));
}

void sMainTest::tick(){
    // Call base
    Scene::tick();
}
