#include <iostream>
#include "engine/input.hpp"
#include "engine/entity.hpp"
#include "engine/scene.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/sceneManager.hpp"

Scene::Scene(Engine& engine) :
    engine(engine) {

    // Load debug font
    std::filesystem::path path = "./arial.ttf";
    debugFont = std::make_shared<sf::Font>();
    if (!debugFont->openFromFile(path))
    {
        std::cout << "SCENE: Failed to load font './arial.ttf'" << std::endl;
    }

    // Create FPS text
    // debugFpsText = std::make_shared<sf::Text>(sf::Text(*debugFont));
    // debugFpsText->setCharacterSize(24);
    // debugFpsText->setFillColor(sf::Color::Red);
    // debugFpsText->setPosition({10,10});
    // debugFpsText->setString(std::to_string(engine.fps));
    // createEntity(debugFpsText, engine.eSceneManager->getSceneDebugMode());
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
    // Set fpsText to current FPS
    //debugFpsText->setString(std::to_string(engine.fps));
    
    // Check for debug input
    if(engine.eInput->getKeyDown(sf::Keyboard::Scancode::Grave)){
        bool newDebugMode = !engine.eSceneManager->getSceneDebugMode();
        engine.eSceneManager->setSceneDebugMode(newDebugMode);
        std::cout << newDebugMode << "\n";
        loadedEntities[0]->enabled = newDebugMode;
    }

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