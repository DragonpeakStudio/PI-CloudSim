// Copyright ©: 2023 - Rowan Cruse Howse

#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>
namespace eng::rndr
{
class Window
{
    public:
        Window(int width, int height, std::string windowName);
        ~Window();
        void init();

        SDL_Window *window() const;

        int height() const;
        int width() const;

    
    private:
        SDL_Window *m_window;
        int m_width, m_height;
        std::string m_windowName;

};
}
#endif