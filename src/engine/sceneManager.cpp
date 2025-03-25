#include <iostream>
#include "engine/sceneManager.hpp"
#include "engine/scene.hpp"
#include "engine/engine.hpp"
#include "game/scenes/sMainMenu.hpp"
#include "game/scenes/sMainTest.hpp"

SceneManager::SceneManager(Renderer& currentRenderer) : 
    currentRenderer(currentRenderer) {}

void SceneManager::loadScene(int sceneId){
    // Set bool
    sceneChangeThisTick = true;
    
    // Let current scene unload itself
    if(loadedScene != nullptr){
        loadedScene->onSceneUnload();
        oldScene = std::move(loadedScene);
    }

    // TODO: Detach hard-coded scenes from /engine side and allow games to register scenes as engine boots
    // Create unique ptr to new scene depending on id, default to main menu
    switch(sceneId){
        case 0:
        loadedScene = std::make_unique<sMainMenu>(*Engine::getEngine());
        break;

        case 1:
        loadedScene = std::make_unique<sMainTest>(*Engine::getEngine());
        break;

        default:
        std::cout << "SceneManager: Invalid scene ID provided" << std::endl;
        loadedScene = std::make_unique<sMainMenu>(*Engine::getEngine());
        break;
    }
}

void SceneManager::tick(){
    // Reset scene change bit
    sceneChangeThisTick = false;

    // Wipe oldscene if existant
    if(oldScene != nullptr) oldScene.reset();

    // Tick currently loaded scene
    if(loadedScene != nullptr) loadedScene->tick();
}

Scene* SceneManager::getCurrentScene() const {
    return loadedScene.get();
}

bool SceneManager::isSceneChangeThisTick(){
    return sceneChangeThisTick;
}
