#include "camera.h"
#include "renderer.h"
#include "engine.h"
eng::rndr::Camera::Camera(float fov, float aspect, float near, float far, glm::vec3 pos, glm::vec3 dir, glm::vec3 up) : m_fov(fov), m_aspect(aspect), m_near(near), m_far(far), m_pos(pos), m_dir(dir), m_up(up)
{
    
}


glm::mat4 eng::rndr::Camera::getView() const
{
    return glm::lookAt(m_pos, m_dir+m_pos, m_up);
}
void eng::rndr::Camera::draw(rndr::Renderer &renderer)
{
    renderer.setViewMat(getView());
    renderer.setProjMat(getProjection());
    renderer.setNearPlane(m_near);
    renderer.setFarPlane(m_far);

    m_isUiShown = renderer.isUiShown();//this is a total bodge to allow disabling mouse motion when ui is off
}
void eng::rndr::Camera::update(double delta)
{
    //key movement
    glm::vec3 moveState = glm::vec3(0);
    moveState.y += m_engine->inputManager().getKeybindState(SDL_SCANCODE_W);
    moveState.y -= m_engine->inputManager().getKeybindState(SDL_SCANCODE_S);
    moveState.x -= m_engine->inputManager().getKeybindState(SDL_SCANCODE_A);
    moveState.x += m_engine->inputManager().getKeybindState(SDL_SCANCODE_D);
    moveState.z -= m_engine->inputManager().getKeybindState(SDL_SCANCODE_SPACE);
    moveState.z += m_engine->inputManager().getKeybindState(SDL_SCANCODE_LSHIFT);

    glm::vec3 side = cross(m_up, m_dir);

    m_pos += (moveState.x*side+moveState.y*m_dir+moveState.z*m_up)*delta*m_moveSpeed;

}
void eng::rndr::Camera::onAdd(Engine *engine)
{
    Object::onAdd(engine);
    m_engine->inputManager().addEventCallback(SDL_MOUSEMOTION, std::bind(&Camera::mouseMotion, this, std::placeholders::_1));
}
void eng::rndr::Camera::drawUI()
{
    ImGui::Begin("Camera");
    ImGui::Text("Cam Pos: %f, %f, %f", m_pos.x, m_pos.y, m_pos.z);
    ImGui::Text("Cam Dir: %f, %f, %f", m_dir.x, m_dir.y, m_dir.z);
	ImGui::End();
}
void eng::rndr::Camera::mouseMotion(const SDL_Event &event)
{
    if(!m_isUiShown)m_dir = glm::angleAxis(-event.motion.yrel*m_mouseSpeed, glm::cross(m_dir, glm::vec3(0,0,1)))*glm::quat(glm::vec3(0, 0, -event.motion.xrel*m_mouseSpeed))*m_dir;
}
glm::mat4 eng::rndr::Camera::getProjection() const
{
    return glm::perspective(m_fov, m_aspect, m_near, m_far);
}