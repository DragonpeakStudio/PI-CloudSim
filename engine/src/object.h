#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <glm/glm.hpp>
namespace eng
{
class Engine;
namespace rndr{class Renderer;};
class Object//this doesn't need to be fast, we will only have ~3-4 ever
{
    public:
        virtual void draw([[maybe_unused]]rndr::Renderer &renderer){};
        virtual void update([[maybe_unused]]double delta){};
        virtual void onAdd(Engine *engine){m_engine = engine;}
        virtual void drawUI(){}
    protected:
        Engine *m_engine = nullptr; 
};
}

#endif // DRAWABLE_H
