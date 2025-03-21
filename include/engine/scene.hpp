#pragma once

#include <vector>
#include <memory>
#include "sfml_includes.hpp"

class Engine;
class Entity;

class Scene{
    public:
        Scene(Engine& engine);
        virtual void tick(); // Called by scene manager every engine tick
        void onSceneUnload(); // Called by scene manager when scene is unloaded

        std::shared_ptr<Entity> getEntityById(int id); // Returns shared_ptr to entity {id}

    protected:
        std::unordered_map<int, std::shared_ptr<Entity>> loadedEntities; // Contains all entities in the scene, key is their assigned id
        Engine& engine; // Reference to engine

        /// @brief Creates an entity and adds it to the loaded entities list. Returns shared_ptr to new entity
        /// @param object The sf::Drawable that should be rendered for the entity
        /// @param enabled If the entity is enabled, dictates if it should be rendered
        std::shared_ptr<Entity> createEntity(bool enabled = true);

        std::shared_ptr<sf::Font> debugFont{nullptr}; // The font for debug text, can be used for any other text
        std::shared_ptr<sf::Text> debugFpsText{nullptr}; // The text that shows current framerate

    private:
    uint32_t currentEntityId{0}; // Increments every time an entity is created to provide a unique id
};