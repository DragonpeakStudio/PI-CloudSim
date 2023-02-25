// Copyright ©: 2023 - Rowan Cruse Howse

#include "renderer.h"
#include "engine.h"
namespace eng::rndr
{
Renderer::Renderer(RendererConfig config, Engine *eng) : m_window(config.width, config.height, config.windowName), m_engine(eng)
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

	m_engine->inputManager().addKeybindCallback(SDL_SCANCODE_1, [&isUiShown = m_isUiShown](){
		isUiShown = !isUiShown;
		SDL_SetRelativeMouseMode((SDL_bool)!isUiShown);
		
	});

	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	m_imguiIo = ImGui::GetIO();

    ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(m_window.window(), m_glContext);
	ImGui_ImplOpenGL3_Init("#version 150");

}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(m_glContext);
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
void Renderer::dispatchFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(m_isUiShown)
	{
		drawUI();
		for(auto & i : m_drawables)
		{
			i->drawUI();
		}
	}
	for(auto & i : m_drawables)
	{
		i->draw(this);
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
void Renderer::drawUI()
{
	ImGui::Begin("status");
	ImGui::Text("Delta : %f", m_engine->delta());
	ImGui::Text("FPS : %f", 1.f/m_engine->delta());
	ImGui::End();
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