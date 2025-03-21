#include "game/scenes/sMainTest.hpp"
#include "game/components/sprite.hpp"

#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/input.hpp"
#include "engine/entity.hpp"
#include <iostream>

sMainTest::sMainTest(Engine& engine) :
    Scene(engine) {
        
    // Create player
    player = std::make_shared<sf::CircleShape>(50.f);
    player->setFillColor(sf::Color::Blue);
    player->setOutlineThickness(5.f);
    player->setOutlineColor(sf::Color::Cyan);
    std::shared_ptr<Entity> playerEntity = createEntity();
    std::shared_ptr<Sprite> playerSprite = std::make_shared<Sprite>(playerEntity, player);
    playerEntity->addComponent(playerSprite);
}

void sMainTest::tick(){
    // Call base
    Scene::tick();

    // Movement test
    float speed = engine.eInput->getKey(sf::Keyboard::Scancode::LShift) ? 5 : 2.5f;

    if(engine.eInput->getKey(sf::Keyboard::Scancode::S)){
        player->move({0.f, speed});
    }
    if(engine.eInput->getKey(sf::Keyboard::Scancode::W)){
        player->move({0.f, -speed});
    }
    if(engine.eInput->getKey(sf::Keyboard::Scancode::A)){
        player->move({-speed, 0});
    }
    if(engine.eInput->getKey(sf::Keyboard::Scancode::D)){
        player->move({speed, 0});
    }
}