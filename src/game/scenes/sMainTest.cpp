#include "game/scenes/sMainTest.hpp"
#include "game/components/sprite.hpp"
#include "game/components/voronoidiagram.hpp"
#include "game/components/view.hpp"
#include "game/components/fpsText.hpp"

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

    // Create fps counter
    voronoiEntity->addComponent(std::make_shared<FPSText>(debugFont));
}

void sMainTest::tick(){
    // Call base
    Scene::tick();
}
