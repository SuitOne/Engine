#include <iostream>
#include "engine/engine.hpp"
#include "engine/input.hpp"
#include "engine/renderer.hpp"
#include "engine/sceneManager.hpp"
#include <filesystem>

Engine* Engine::pEngine = nullptr;

Engine::Engine() :
    eRenderer(nullptr),
    eInput(nullptr),
    eSceneManager(nullptr),
    deltaTime(sf::Time::Zero),
    fps(1000) {}

void Engine::mainLoop(){
    // Create the window, initialize renderer
    renderWindow = sf::RenderWindow(sf::VideoMode({1280, 720}), "SFML_Test");
    renderWindow.setVerticalSyncEnabled(true);
    renderWindow.setKeyRepeatEnabled(false);
    eRenderer = std::make_unique<Renderer>(renderWindow);

    // Create the input manager
    eInput = std::make_unique<Input>(true);

    // Create the scene manager
    eSceneManager = std::make_unique<SceneManager>(*eRenderer);

    // Create deltaTime clock
    sf::Clock deltaTimeClock;

    // Load initial scene
    eSceneManager->loadScene(0);
    
    // Run the program as long as the window is open
    while (Engine::renderWindow.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        /*
        ORDER OF OPERATIONS PER TICK:
        -RESET INPUT
        -CHECK FOR WINDOW CLOSE
        -GET INPUT, PASS TO INPUT MANAGER
        -SCENE TICK
        -RENDERER DRAWS FRAME
        -DELTATIME CALCULATED
        */

        // Reset input
        eInput->resetInput();

        while (const std::optional event = renderWindow.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()){
                renderWindow.close();
            }   

            // Process user input
            if(const auto& keyPressed = event->getIf<sf::Event::KeyPressed>()){
                eInput->parseInput(keyPressed->scancode, true);
            } else if(const auto& keyReleased = event->getIf<sf::Event::KeyReleased>()){
                eInput->parseInput(keyReleased->scancode, false);
            }

            // Kill command
            if(eInput->getKey(sf::Keyboard::Scancode::Escape)) renderWindow.close();
        }

        // Scene tick
        eSceneManager->tick();

        // Rendering
        eRenderer->drawFrame();

        // Clock deltatime
        deltaTime = deltaTimeClock.restart();
        fps = deltaTime.asMilliseconds() == 0 ? 1000 : 1000 / deltaTime.asMilliseconds();
        //std::cout << "DeltaTime: " << deltaTime.asMilliseconds() << " FPS: " << fps << std::endl;
    }
}

