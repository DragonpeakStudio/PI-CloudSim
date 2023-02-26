#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include <glm/gtc/quaternion.hpp>
#include <SDL2/SDL.h>
#include "object.h"
namespace eng::rndr
{
class Camera : public Object
{
    public:
        Camera(float fov, float aspect, float near = 0.01f, float far=1000.f, glm::vec3 pos = glm::vec3(0.f,1.f,0.f), glm::vec3 dir = glm::vec3(0.f, 1.f, 0.f), glm::vec3 up = glm::vec3(0.f,0.f,-1.f));
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;

        virtual void draw(rndr::Renderer *renderer) override;
        virtual void update(double delta, Engine *engine) override;
        virtual void onAdd(Engine *engine) override;


    private:
        void mouseMotion(const SDL_Event &event);

        float m_fov;
        float m_aspect;

        float m_near;
        float m_far;
        glm::vec3 m_pos;
        glm::vec3 m_dir;
        glm::vec3 m_up;

        float m_moveSpeed = 100.;
        float m_mouseSpeed = .01;
        bool m_isUiShown = false;
};
}

#endif // CAMERA_H
