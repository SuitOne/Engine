#include "game/components/sprite.hpp"
#include "engine/engine.hpp"
#include "engine/renderer.hpp"
#include "engine/entity.hpp"

Sprite::Sprite(std::weak_ptr<Entity> owner, std::shared_ptr<sf::Drawable> drawable) :
    drawable(drawable) {
    setOwner(owner);
    drawable = std::move(drawable);
}

void Sprite::init(){

}

void Sprite::tick(){
    Engine::getEngine()->eRenderer->addRenderCommand(drawable);
}
