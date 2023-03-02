#include "outdoorlighting.h"

OutdoorLighting::OutdoorLighting()
{

}

OutdoorLighting::~OutdoorLighting()
{

}
void OutdoorLighting::drawUI()
{
    ImGui::Begin("Light");
    ImGui::ColorEdit3("Sun Colour", &m_sunCol.x);
    ImGui::ColorEdit3("Ambient Colour", &m_ambientCol.x);
    m_hasDirChanged = ImGui::SliderFloat2("Sun Dir", &m_sunSpherical.x, -3.14, 3.14);
    ImGui::End();
}
glm::vec3 OutdoorLighting::ambientCol() const
{
    return m_ambientCol;
}

glm::vec3 OutdoorLighting::sunDir() const
{
    return glm::vec3(sin(m_sunSpherical.x)*cos(m_sunSpherical.y), sin(m_sunSpherical.x)*sin(m_sunSpherical.y), cos(m_sunSpherical.x));

}

glm::vec3 OutdoorLighting::sunCol() const
{
    return m_sunCol;
}

bool OutdoorLighting::hasDirChanged() const
{
    return m_hasDirChanged;
}
