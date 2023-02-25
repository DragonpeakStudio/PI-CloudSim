#ifndef ENGINE_H
#define ENGINE_H

#pragma once

#include <SDL2/SDL.h>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include "inputmanager.h"
#include "renderer.h"
#include "camera.h"

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
		void addObject(std::shared_ptr<Object> obj);
		InputManager &inputManager();
	private:
		void mainLoop();
		void update(double delta);
		EngineState m_state = WAITING;
		InputManager m_inputManager;
		rndr::Renderer m_renderer;
		std::vector<std::shared_ptr<Object>> m_objects;

};
}
#endif