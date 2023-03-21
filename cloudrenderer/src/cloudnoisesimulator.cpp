#include "cloudnoisesimulator.h"

CloudNoiseSimulator::CloudNoiseSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale) : CloudSimulator(bbox, voxelScale), 
m_densField(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RED, 1, GL_R16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale),
m_noiseProcess("../resources/shaders/noisesimprocess.comp"),
m_slicer(m_densField)
{
    m_noiseProcess.load();
}

void CloudNoiseSimulator::update(double delta)
{
    m_time+=delta;
    m_noiseProcess.bind();
    m_noiseProcess.setUniform("bboxMin", m_bbox.first);
    m_noiseProcess.setUniform("bboxMax", m_bbox.second);
    m_noiseProcess.setUniform("time", (float)m_time*m_windSpeed);
    glm::vec3 windDir = glm::vec3(cos(m_windAngle), sin(m_windAngle),0);
    m_noiseProcess.setUniform("windDir", windDir);

    glBindImageTexture(1, m_densField.id(), 0, false, 0, GL_READ_WRITE, GL_R16F);
    m_noiseProcess.dispatch(glm::uvec3(m_densField.width()/8, m_densField.height()/8, m_densField.depth()/8));
    glUseProgram(0);

}

eng::rndr::Texture3d &CloudNoiseSimulator::getField(std::string_view identifier)
{
    assert(identifier=="density");
    return m_densField;
}

void CloudNoiseSimulator::drawUI()
{
    ImGui::Begin("Cloud Sim");
    ImGui::SliderAngle("Wind Dir", &m_windAngle);
    ImGui::SliderFloat("Wind Speed", &m_windSpeed, 0., 1.);
    ImGui::SliderInt("Slice", &m_debugSlice, 0, m_densField.depth());
    m_slicer.update(m_debugSlice);
    ImGui::Image((void*)(intptr_t)m_slicer.getSlice()->id(), {(float)256.f, (float)256.f});
    ImGui::End();
}
