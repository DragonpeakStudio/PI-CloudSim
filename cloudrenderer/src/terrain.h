#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include <vector>
#include "texture2d.h"
#include "computeshaderprogram.h"
#include "vfshaderprogram.h"
#include "object.h"
#include "glutil.h"
#include "outdoorlighting.h"
class Terrain : public eng::Object
{

    public:
        Terrain(std::weak_ptr<OutdoorLighting> lighting, std::unique_ptr<eng::rndr::Texture2d> heightMap,
        std::unique_ptr<eng::rndr::Texture2d> colMap,
        unsigned int sizeX,
        unsigned int sizeY,
        unsigned int resX,
        unsigned int resY,
        std::unique_ptr<eng::rndr::VFShaderProgram> drawShader = std::make_unique<eng::rndr::VFShaderProgram>("../resources/shaders/mvp.vert", "../resources/shaders/terrain.frag"), 
        std::unique_ptr<eng::rndr::ComputeShaderProgram> terrainGenShader = std::make_unique<eng::rndr::ComputeShaderProgram>("../resources/shaders/terraingen.comp"),
        std::unique_ptr<eng::rndr::ComputeShaderProgram> shadowMapShader = std::make_unique<eng::rndr::ComputeShaderProgram>("../resources/shaders/calcterrainshadow.comp"));
        virtual ~Terrain();
        void generate();
        virtual void draw(eng::rndr::Renderer *renderer) override;
        virtual void drawUI() override;
    private:
        struct Vert
        {
            glm::vec4 position;
            glm::vec4 normal;
            glm::vec4 uv;
        };
        std::weak_ptr<OutdoorLighting> m_lighting;

        std::vector<Vert> m_vertexGrid;
        std::vector<GLuint> m_elements;

        std::unique_ptr<eng::rndr::Texture2d> m_heightMap;
        std::unique_ptr<eng::rndr::Texture2d> m_colMap;

        unsigned int m_sizeX;
        unsigned int m_sizeY;

        unsigned int m_resX;
        unsigned int m_resY;

        std::unique_ptr<eng::rndr::VFShaderProgram> m_drawShader;
        std::unique_ptr<eng::rndr::ComputeShaderProgram> m_terrainGenShader;
        std::unique_ptr<eng::rndr::ComputeShaderProgram> m_shadowMapShader;


        GLuint m_vbo = 0;
        GLuint m_ebo = 0;
        GLuint m_vao = 0;

        float m_shadowK = 32.;
        float m_shadowStep = 20.;
        float m_shadowFar = 1000.;
        bool m_hasShadowParamsChanged = true;

        void updateShadows();





};

#endif