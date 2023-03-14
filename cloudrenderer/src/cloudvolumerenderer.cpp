#include "cloudvolumerenderer.h"

CloudVolumeRenderer::CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox) : CloudRenderer(bbox)
{

}

void CloudVolumeRenderer::draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer)
{
    //TODO
}
