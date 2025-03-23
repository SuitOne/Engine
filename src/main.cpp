#include "engine/engine.hpp"
int main()
{
    Engine* engine = Engine::getEngine();
    engine->mainLoop();

    return 0;
}
