#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>
#include "inputmanager.h"
#include "renderer.h"

namespace eng
{
struct EngineConfig
{
	rndr::RendererConfig renderConfig;
};  
class Engine
{
   public:
		enum EngineState
		{
			RUNNING,
			STOPPED,
			ERROR,
			WAITING,
		};
		Engine(EngineConfig &&config);
		~Engine();
		void run();
		void exit();
	private:
		void mainLoop();
		EngineState m_state = WAITING;
		InputManager m_inputManager;
		rndr::Renderer m_renderer;
};
}
#endif