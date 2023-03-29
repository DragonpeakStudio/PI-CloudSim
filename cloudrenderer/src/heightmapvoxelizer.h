#pragma once
#ifndef HEIGHTMAPVOXELIZER_H
#define HEIGHTMAPVOXELIZER_H

#include <memory>
#include "texture3d.h"
#include "texture2d.h"

#include "computeshaderprogram.h"

std::unique_ptr<eng::rndr::Texture3d> voxelizeHeightMap(eng::rndr::Texture2d *map, std::pair<glm::vec3, glm::vec3> bbox, float voxelScale);

#endif // HEIGHTMAPVOXELIZER_H
