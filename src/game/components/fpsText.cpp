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
    pEngine->eRenderer->addDrawable(std::make_shared<sf::Text>(text));
}
