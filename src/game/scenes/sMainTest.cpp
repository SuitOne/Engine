#include "game/scenes/sMainTest.hpp"
#include "game/components/sprite.hpp"
#include "game/components/voronoidiagram.hpp"
#include "game/components/view.hpp"

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

    // Create view
    voronoiEntity->addComponent(std::make_shared<View>());
}

void sMainTest::tick(){
    // Call base
    Scene::tick();
}
