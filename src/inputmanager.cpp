// Copyright ©: 2023 - Rowan Cruse Howse

#include "inputmanager.h"
#include "engine.h"
namespace eng
{
InputManager::InputManager(Engine * engine) : m_engine(engine)
{

}

InputManager::~InputManager()
{

}
void InputManager::processEvents()
{

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        for(auto &i : m_events[(SDL_EventType)event.type])
        {
            i(event);
        }
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        m_engine->exit();
                        break;
                    default:
                        break;
                    

                }
                break;
            case SDL_KEYDOWN:
                if(m_keybinds.find(event.key.keysym.scancode)!=m_keybinds.end())m_keybinds[event.key.keysym.scancode]();
                break;

            default:
                break;
                

        }
	}

}

void InputManager::addKeybindCallback(SDL_Scancode key, std::function<void()> callback)
{
    m_keybinds[key] = callback;
}

bool InputManager::getKeybindState(SDL_Scancode key)
{
    const Uint8 *keyStates = SDL_GetKeyboardState(nullptr);
    return keyStates[key];
}

void InputManager::addEventCallback(SDL_EventType type, std::function<void(const SDL_Event&)> callback)
{
    if(m_events.find(type)==m_events.end())
    {
        m_events[type] = std::vector<std::function<void(const SDL_Event&)>>();
    }
    m_events[type].push_back(callback);
}
}