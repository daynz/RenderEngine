#include "Engine.hpp"

// Main code
int main(int, char**)
{
    Engine* engine = Engine::instance(1920, 1080);

    // Main loop
    engine->setModel();
    
    engine->renderLoop();

    // Cleanup
    Engine::clearup();

    return 0;
}
