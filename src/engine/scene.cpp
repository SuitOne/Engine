#include <iostream>
#include "engine/input.hpp"
#include "engine/entity.hpp"
#include "engine/scene.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/sceneManager.hpp"

Scene::Scene(Engine& engine) :
    engine(engine) {

    // THESE NEED TO BE MOVED TO A RESOURCE MANAGER, NOT THE MAIN SCENE CLASS //
    // Load debug font
    std::filesystem::path path = "./arial.ttf";
    debugFont = std::make_shared<sf::Font>();
    if (!debugFont->openFromFile(path))
    {
        std::cout << "SCENE: Failed to load font './arial.ttf'" << std::endl;
    }
    // THESE NEED TO BE MOVED TO A RESOURCE MANAGER, NOT THE MAIN SCENE CLASS //
}

std::shared_ptr<Entity> Scene::createEntity(bool enabled){
    loadedEntities[currentEntityId] = std::make_shared<Entity>(currentEntityId, enabled);
    currentEntityId++;

    return loadedEntities[currentEntityId - 1];
}

std::shared_ptr<Entity> Scene::getEntityById(int id){
    return loadedEntities[id];
}

void Scene::tick(){    
    // Tick entities
    for(auto entity : loadedEntities){
        if(entity.second->enabled) {
            entity.second->tick();
        }
    }
}

void Scene::onSceneUnload(){
    loadedEntities.clear();
    engine.eRenderer->clearDrawables();
}
