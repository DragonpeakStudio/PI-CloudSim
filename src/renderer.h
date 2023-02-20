// Copyright ©: 2023 - Rowan Cruse Howse

#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <GL/glew.h>

#include "window.h"
namespace eng::rndr
{
struct RendererConfig
{
	std::string m_windowName;
	int m_width, m_height;
	int m_glMajorVersion, m_glMinorVersion;
};
class Renderer
{
    public:
        Renderer(RendererConfig config);
        ~Renderer();
        void dispatchFrame();
    
    private:
        void drawSprites();
        Window m_window;
        SDL_GLContext m_glContext;

};
}
#endif