#include "engine.h"
namespace eng
{
Engine::Engine(EngineConfig &&config) : m_inputManager(this)
{
	m_inputManager.addKeybindCallback(SDL_SCANCODE_ESCAPE, [this](){exit();});
}

Engine::~Engine()
{

}

void Engine::run()
{
	m_state = RUNNING;
	mainLoop();
}

void Engine::exit()
{
	m_state = STOPPED;
}
void Engine::mainLoop()
{
    while(m_state == EngineState::RUNNING)
    {
        m_inputManager.processEvents();
    }
}
}