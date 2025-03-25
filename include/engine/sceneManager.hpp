#pragma once

#include <vector>
#include <memory>
#include <string>
#include "engine/scene.hpp"

class Renderer;
class Scene;

class SceneManager {
    private:
        Renderer& currentRenderer;
        std::unique_ptr<Scene> loadedScene {nullptr};
        std::unique_ptr<Scene> oldScene {nullptr}; // nullptr unless the scene was discarded on the current tick
        bool sceneChangeThisTick {false}; // True if a scene change was initiated on the current tick

    public:
        SceneManager(Renderer& currentRenderer);

        /// @brief Deletes the currently loaded scene, then creates and loads a new scene
        /// @param sceneId ID of scene to load, starting at 0 for the main menu
        void loadScene(int sceneId);

        /// @brief Called by the main loop each loop
        void tick();

        /// @brief Returns true if scene change was initiated this tick
        bool isSceneChangeThisTick();

        /// @brief Returns the currently loaded scene
        Scene* getCurrentScene() const;
};
