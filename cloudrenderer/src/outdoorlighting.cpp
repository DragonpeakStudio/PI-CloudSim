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
    ImGui::SliderFloat("Sun Mult", &m_sunMult, 0., 20.);

    ImGui::ColorEdit3("Ambient Colour", &m_ambientCol.x);
    ImGui::SliderFloat("Ambient Mult", &m_ambientMult, 0., 20.);

    //m_hasDirChanged = ImGui::SliderFloat2("Sun Dir", &m_sunSpherical.x, -3.14, 3.14);
    m_hasDirChanged = ImGui::SliderAngle("Sun Height", &m_sunSpherical.x, -180.f, 180.f);
    m_hasDirChanged = m_hasDirChanged||ImGui::SliderAngle("Sun Dir", &m_sunSpherical.y, -180.f, 180.f);


    ImGui::End();
}
glm::vec3 OutdoorLighting::ambientCol() const
{
    return m_ambientCol*m_ambientMult;
}

glm::vec3 OutdoorLighting::sunDir() const
{
    return glm::vec3(sin(m_sunSpherical.x)*cos(m_sunSpherical.y), sin(m_sunSpherical.x)*sin(m_sunSpherical.y), cos(m_sunSpherical.x));

}

glm::vec3 OutdoorLighting::sunCol() const
{
    return m_sunCol*m_sunMult;
}

bool OutdoorLighting::hasDirChanged() const
{
    return m_hasDirChanged;
}
