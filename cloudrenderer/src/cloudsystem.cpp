#include "cloudsystem.h"
std::pair<glm::vec3, glm::vec3> CloudSystem::bbox() const
{
    return m_bbox;
}
void CloudSystem::update(double delta)
{
    m_simulator->update(delta);
}
void CloudSystem::drawUI()
{
    //TODO
}
void CloudSystem::draw(eng::rndr::Renderer &renderer)
{
    m_renderer->draw(m_simulator->getField("density"), renderer);
}
