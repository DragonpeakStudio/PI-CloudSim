// Copyright ©: 2023 - Rowan Cruse Howse

#include "renderer.h"
namespace eng::rndr
{
Renderer::Renderer(RendererConfig config) : m_window(config.m_width, config.m_height, config.m_windowName)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		throw std::runtime_error("Unable to Init SDL");
	}
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, config.m_glMajorVersion );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, config.m_glMinorVersion );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    m_window.init();

    m_glContext = SDL_GL_CreateContext(m_window.window());
	if(m_glContext==nullptr)
	{
		throw std::runtime_error("Unable to Create GL Context");
	}
	glewExperimental = true;
	if(glewInit()!=GLEW_OK)
	{
		throw std::runtime_error("Unable to Init GLEW");
	}
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(m_glContext);
}
void Renderer::dispatchFrame()
{
    
}
}