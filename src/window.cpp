// Copyright ©: 2023 - Rowan Cruse Howse

#include "window.h"
namespace eng::rndr
{
Window::Window(int width, int height, std::string windowName) : m_width(width), m_height(height), m_windowName(windowName)
{

}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}
void Window::init()
{
	m_window = SDL_CreateWindow(m_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(m_window==nullptr)
	{
		throw std::runtime_error("Unable to Create Window");
	}
}
SDL_Window *Window::window() const
{
    return m_window;
}
}