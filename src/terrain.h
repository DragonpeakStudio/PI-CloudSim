#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <vector>
#include "texture2d.h"
#include "computeshaderprogram.h"
#include "vfshaderprogram.h"
#include "object.h"
#include "glutil.h"
class Terrain : public eng::Object
{

    public:
        Terrain(std::unique_ptr<eng::rndr::Texture2d> heightMap,
        std::unique_ptr<eng::rndr::Texture2d> colMap,
        unsigned int sizeX,
        unsigned int sizeY,
        std::unique_ptr<eng::rndr::VFShaderProgram> drawShader = std::make_unique<eng::rndr::VFShaderProgram>("resources/shaders/mvp.vert", "resources/shaders/terrain.frag"), 
        std::unique_ptr<eng::rndr::ComputeShaderProgram> terrainGenShader = std::make_unique<eng::rndr::ComputeShaderProgram>("resources/shaders/terraingen.comp"));
        void generate();
        virtual void draw(eng::rndr::Renderer *renderer) override;
        virtual void update([[maybe_unused]]double delta, [[maybe_unused]]eng::Engine *engine) override{};
    private:
        struct Vert
        {
            glm::vec4 position;
            glm::vec4 normal;
            glm::vec4 uv;
        };
        std::vector<Vert> m_vertexGrid;
        std::vector<GLuint> m_elements;

        std::unique_ptr<eng::rndr::Texture2d> m_heightMap;
        std::unique_ptr<eng::rndr::Texture2d> m_colMap;

        unsigned int m_sizeX;
        unsigned int m_sizeY;

        std::unique_ptr<eng::rndr::VFShaderProgram> m_drawShader;
        std::unique_ptr<eng::rndr::ComputeShaderProgram> m_terrainGenShader;

        GLuint m_vbo = 0;
        GLuint m_ebo = 0;
        GLuint m_vao = 0;



};

#endif