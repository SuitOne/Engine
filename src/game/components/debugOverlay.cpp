#include "game/components/debugOverlay.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/input.hpp"
#include <iostream>

DebugOverlay::DebugOverlay(std::shared_ptr<sf::Font> debugFont) :
fpsText(sf::Text(*debugFont, "", 24)),
backdrop({150.f, 100.f}) {

    fpsText.setFillColor(sf::Color::Red);

    backdrop.setFillColor(sf::Color(1, 1, 1, 128));

    pEngine = Engine::getEngine();
}

void DebugOverlay::init() {

}

void DebugOverlay::tick() {
    // Check to see if toggled, enabled
    if(pEngine->eInput->getKeyDown(sf::Keyboard::Scancode::Grave)){
        enabled = !enabled;
    }

    if(!enabled) return;

    // Set fps text
    fpsText.setString("FPS: " + std::to_string(pEngine->fps));

    sf::Vector2f viewCenter = pEngine->renderWindow.getView().getCenter();
    sf::Vector2f viewSize = pEngine->renderWindow.getView().getSize();
    
    fpsText.setPosition(viewCenter + sf::Vector2f{viewSize.x / -2 + 10, viewSize.y / -2 + 10});
    backdrop.setPosition(viewCenter + sf::Vector2f{viewSize.x / -2 + 10, viewSize.y / -2 + 10});

    pEngine->eRenderer->addRenderCommand(std::make_shared<sf::Text>(fpsText), 999);
    pEngine->eRenderer->addRenderCommand(std::make_shared<sf::RectangleShape>(backdrop), 1000);
}
