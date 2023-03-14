#include "cloudnoisesimulator.h"

CloudNoiseSimulator::CloudNoiseSimulator(std::pair<glm::vec3, glm::vec3> bbox, float voxelScale) : CloudSimulator(bbox, voxelScale), 
m_densField(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_R, 1, GL_R16F, GL_FLOAT}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale)
{

}

void CloudNoiseSimulator::update(double delta)
{
    //TODO
}

eng::rndr::Texture3d &CloudNoiseSimulator::getField(std::string_view identifier)
{
    // TODO: insert return statement here
    assert(identifier=="density");
    return m_densField;
}
