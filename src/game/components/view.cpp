#include "game/components/view.hpp"
#include "engine/engine.hpp"
#include "engine/input.hpp"
#include "engine/renderer.hpp"

void View::init(){
    engine = Engine::getEngine();
    mainView = sf::View({0.f, 0.f}, engine->renderWindow.getDefaultView().getSize());

    engine->eRenderer->setMainView(mainView);
}

void View::tick(){
    float zoomSpeed = 1.f * engine->deltaTime.asSeconds();
    float moveSpeed = 500.f * engine->deltaTime.asSeconds();

    if(engine->eInput->getKey(sf::Keyboard::Scancode::Comma)){
        mainView.zoom(1 + zoomSpeed);
    }

    if(engine->eInput->getKey(sf::Keyboard::Scancode::Period)){
        mainView.zoom(1 - zoomSpeed);
    }

    if(engine->eInput->getKey(sf::Keyboard::Scancode::W)){
        mainView.move({0.f, -moveSpeed});
    }

    if(engine->eInput->getKey(sf::Keyboard::Scancode::S)){
        mainView.move({0.f, moveSpeed});
    }

    if(engine->eInput->getKey(sf::Keyboard::Scancode::A)){
        mainView.move({-moveSpeed, 0.f});
    }

    if(engine->eInput->getKey(sf::Keyboard::Scancode::D)){
        mainView.move({moveSpeed, 0.f});
    }

    engine->eRenderer->setMainView(mainView);
}
