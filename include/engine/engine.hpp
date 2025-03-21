#pragma once

#include <memory>
#include "sfml_includes.hpp"

class Renderer;
class Input;
class SceneManager;

class Engine{
    private:
        static Engine* pEngine;
   
    public:
        // Delete copy constructor
        Engine(const Engine& obj) = delete;

        // Singleton constructor
        static Engine* getEngine(){
            if(pEngine == nullptr) {
                pEngine = new Engine();
            }
            return pEngine;
        }

        std::unique_ptr<Renderer> eRenderer;
        std::unique_ptr<Input> eInput;
        std::unique_ptr<SceneManager> eSceneManager;
        sf::RenderWindow renderWindow;
        sf::Time deltaTime;
        int fps;

        void mainLoop();

    private:
        Engine();
};