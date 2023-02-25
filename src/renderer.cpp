// Copyright ©: 2023 - Rowan Cruse Howse

#include "renderer.h"
namespace eng::rndr
{
Renderer::Renderer(RendererConfig config) : m_window(config.width, config.height, config.windowName)
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		throw std::runtime_error("Unable to Init SDL");
	}
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, config.glMajorVersion );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, config.glMinorVersion );
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
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_CULL_FACE);  
	glEnable(GL_DEPTH_TEST);
	// glEnable( GL_DEBUG_OUTPUT );
	// glDebugMessageCallback( GLMessageCallback, 0 );
	glViewport(0, 0, m_window.width(), m_window.height());

}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(m_glContext);
}
void Renderer::dispatchFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(auto & i : m_drawables)
	{
		i->draw(this);
	}
	SDL_GL_SwapWindow(m_window.window());
}
glm::mat4 Renderer::viewMat() const
{
    return m_viewMat;
}
void Renderer::setViewMat(glm::mat4 viewMat)
{
    m_viewMat = viewMat;
}
glm::mat4 Renderer::projMat() const
{
    return m_projMat;
}
void Renderer::setProjMat(const glm::mat4 &projMat)
{
    m_projMat = projMat;
}
void Renderer::addDrawable(std::shared_ptr<Object> obj)
{
	m_drawables.push_back(obj);
}
}