#include "cloudrenderer.h"

CloudRenderer::CloudRenderer(std::pair<glm::vec3, glm::vec3> bbox, std::weak_ptr<OutdoorLighting> lighting) : m_bbox(bbox), m_lighting(lighting)
{
}
