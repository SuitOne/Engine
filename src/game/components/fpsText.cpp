#include "game/components/fpsText.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include <iostream>

FPSText::FPSText(std::shared_ptr<sf::Font> debugFont) :
text(sf::Text(*debugFont, "", 24)) {
    text.setFillColor(sf::Color::Red);
    text.setPosition({10,10});

    pEngine = Engine::getEngine();
}

void FPSText::init() {

}

void FPSText::tick() {
    text.setString(std::to_string(pEngine->fps));

    sf::Vector2f viewCenter = pEngine->renderWindow.getView().getCenter();
    sf::Vector2f viewSize = pEngine->renderWindow.getView().getSize();
    
    text.setPosition(viewCenter + sf::Vector2f{viewSize.x / -2 + 10, viewSize.y / -2 + 10});

    pEngine->eRenderer->addDrawable(std::make_shared<sf::Text>(text));
}
