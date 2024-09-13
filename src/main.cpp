#include "Engine.hpp"

// Main code
int main(int, char**)
{
    Engine* engine = Engine::instance(1920, 1080);

    // Main loop
    engine->renderLoop();
    engine->setModel();
    engine->setOpenGL();

    // Cleanup
    Engine::clearup();

    return 0;
}
