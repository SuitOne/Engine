#pragma once

#include <memory>
#include <vector>
#include <sfml_includes.hpp>

class Component;

class Entity {
    public:
        Entity(uint32_t id, bool startEnabled = true);    
        
        void addComponent(std::shared_ptr<Component> component);
        void tick();

        uint32_t getId();

        template <typename T>
        std::shared_ptr<T> getComponent(T typeOfComponent);

        bool enabled;
    
    private:
        std::vector<std::shared_ptr<Component>> components;
        uint32_t id;
};