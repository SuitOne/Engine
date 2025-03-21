#include "engine/entity.hpp"
#include "engine/component.hpp"

Entity::Entity(uint32_t id, bool startEnabled) :
    id(id), 
    enabled(startEnabled) {}

void Entity::addComponent(std::shared_ptr<Component> component) {
    components.push_back(component);
    component->init();
}

void Entity::tick(){
    for(auto c : components){
        c->tick();
    }
}

uint32_t Entity::getId() {
    return id;
}

template <typename T>
std::shared_ptr<T> Entity::getComponent(T typeOfComponent){
    for (auto& component : components) {
        std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
        if (castedComponent) {
            return castedComponent;
        }
    }

    return nullptr;
}