#include <iostream>

#include "game/scenes/sMainMenu.hpp"
#include "game/components/sprite.hpp"

#include "engine/entity.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/input.hpp"
#include "engine/sceneManager.hpp"

sMainMenu::sMainMenu(Engine& engine) :
    Scene(engine){

    // Create main text
    sf::Text mainText = sf::Text(*debugFont);
    mainText.setCharacterSize(24);
    mainText.setFillColor(sf::Color::Red);
    mainText.setPosition({640, 360});
    mainText.setOrigin({300,300});
    mainText.setString("Press 'SPACE' To Start");

    std::shared_ptr<Entity> mmTextEntity = 
        createEntity();
    mmTextEntity->addComponent(std::make_shared<Sprite>(mmTextEntity, std::make_shared<sf::Text>(mainText)));
}

void sMainMenu::tick(){
    // Call base
    Scene::tick();

    // Scan for input
    if(engine.eInput->getKeyDown(sf::Keyboard::Scancode::Space)){
        engine.eSceneManager->loadScene(1);
    }
}
