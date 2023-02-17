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
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
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
}