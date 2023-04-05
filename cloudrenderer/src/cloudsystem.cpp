#include "cloudsystem.h"
CloudSystem::CloudSystem(std::unique_ptr<CloudRenderer> renderer, std::unique_ptr<CloudSimulator> simulator, std::pair<glm::vec3, glm::vec3> bbox) : m_renderer(std::move(renderer)), m_simulator(std::move(simulator)), m_bbox(bbox)
{

}
std::pair<glm::vec3, glm::vec3> CloudSystem::bbox() const
{
    return m_bbox;
}
void CloudSystem::update(double delta)
{
    m_simulator->update(delta);
}
CloudRenderer *CloudSystem::renderer()
{
    return m_renderer.get();
}
void CloudSystem::drawUI()
{
    //TODO
    m_simulator->drawUI();
    m_renderer->drawUI();
}
void CloudSystem::onAdd(eng::Engine *engine)
{
    eng::Object::onAdd(engine);
    m_simulator->init();
}
CloudSimulator *CloudSystem::simulator()
{
    return m_simulator.get();
}
CloudSystem::~CloudSystem()
{
}
void CloudSystem::draw(eng::rndr::Renderer &renderer)
{
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    m_renderer->draw(m_simulator->getField("density"), renderer);
}
