// Copyright ©: 2023 - Rowan Cruse Howse

#ifndef RENDERER_H
#define RENDERER_H

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <GL/glew.h>
#include <vector>
#include "object.h"
#include "window.h"
#include "glutil.h"
#include "camera.h"
#include "inputmanager.h"
#include "vfshaderprogram.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include "framebuffer.h"
namespace eng{class Engine;}

namespace eng::rndr
{
struct RendererConfig
{
	std::string windowName;
	int width, height;
	int glMajorVersion, glMinorVersion;
    std::string fsqVertShader = "../resources/shaders/basic.vert";
    std::string fsqFragShader = "../resources/shaders/postprocess.frag";

};
class Renderer
{
    public:
        Renderer(RendererConfig config, Engine *eng);
        ~Renderer();
        void dispatchFrame();
        void addDrawable(std::shared_ptr<Object> obj);

        glm::mat4 projMat() const;
        void setProjMat(const glm::mat4 &projMat);
        glm::mat4 viewMat() const;
        void setViewMat(glm::mat4 viewMat);

        bool isUiShown() const;
    
    private:
        void drawUI();
        Window m_window;
        SDL_GLContext m_glContext;
        std::vector<std::shared_ptr<Object>> m_drawables;
        glm::mat4 m_viewMat;
        glm::mat4 m_projMat;
        ImGuiIO m_imguiIo;
        Engine *m_engine;
        bool m_isUiShown = true;
        FrameBuffer m_frameBuffer;


};
}
#endif