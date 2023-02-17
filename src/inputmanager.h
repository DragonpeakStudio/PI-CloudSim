// Copyright ©: 2023 - Rowan Cruse Howse

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma once

#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <unordered_map>
namespace eng
{
class Engine;
class InputManager
{
public:
        InputManager(Engine * engine);
        ~InputManager();

        void processEvents();
        void addKeybindCallback(SDL_Scancode key, std::function<void()> callback);
        bool getKeybindState(SDL_Scancode key);

    private:
        Engine * m_engine;
        std::unordered_map<SDL_Scancode, std::function<void()>> m_keybinds;
};
}
#endif