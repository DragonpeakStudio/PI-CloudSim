#include "heightmapvoxelizer.h"

std::unique_ptr<eng::rndr::Texture3d> voxelizeHeightMap(eng::rndr::Texture2d *map, std::pair<glm::vec3, glm::vec3> bbox, float voxelScale)
{
    auto result = std::make_unique<eng::rndr::Texture3d>(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RED, 1, GL_R8, GL_UNSIGNED_BYTE}, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale, (bbox.second.x-bbox.first.x)/voxelScale);
    eng::rndr::ComputeShaderProgram compute("../resources/shaders/heightmapvoxelize.comp");
    compute.load();
    compute.bind();
    compute.setUniform("bboxMin", bbox.first);
    compute.setUniform("bboxMax", bbox.second);
    glBindImageTexture(1, result->id(), 0, false, 0, GL_READ_WRITE, GL_R8);
    compute.setUniform("heightMap", 0);
    map->bind(GL_TEXTURE0);
    compute.dispatch(glm::uvec3(result->width()/8, result->height()/8, result->depth()/8));

    return result;

}