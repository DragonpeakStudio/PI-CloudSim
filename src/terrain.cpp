#include "terrain.h"
#include "renderer.h"

Terrain::Terrain(std::unique_ptr<eng::rndr::Texture2d> heightMap,
         std::unique_ptr<eng::rndr::Texture2d> colMap,
         unsigned int sizeX,
         unsigned int sizeY,
         std::unique_ptr<eng::rndr::VFShaderProgram> drawShader, 
         std::unique_ptr<eng::rndr::ComputeShaderProgram> terrainGenShader) : m_heightMap(std::move(heightMap)), m_colMap(std::move(colMap)), m_sizeX(sizeX), m_sizeY(sizeY), m_drawShader(std::move(drawShader)), m_terrainGenShader(std::move(terrainGenShader))
{
    m_drawShader->load();
    m_terrainGenShader->load();
}

void Terrain::generate()
{
    m_vertexGrid.reserve(m_sizeX*m_sizeY);
    m_elements.reserve(m_sizeX*m_sizeY*3);
    for(unsigned int x = 0; x < m_sizeX; x++)
    {
        for(unsigned int y = 0; y < m_sizeY; y++)
        {
            m_vertexGrid.push_back(Vert{glm::vec4((float)x - (float)m_sizeX/2., (float)y - (float)m_sizeY/2., 0., 1.), glm::vec4(0,0,0,0), glm::vec4((float)x/(float)m_sizeX, (float)y/(float)m_sizeY,0,0)});
            
        }

    }
    for(unsigned int x = 0; x < m_sizeX-1; x++)
    {
        for(unsigned int y = 0; y < m_sizeY-1; y++)
        {
            m_elements.push_back(x+y*m_sizeX);
            m_elements.push_back(x+(y+1)*m_sizeX);
            m_elements.push_back((x+1)+y*m_sizeX);


            m_elements.push_back(x+(y+1)*m_sizeX);
            m_elements.push_back((x+1)+(y+1)*m_sizeX);
            m_elements.push_back((x+1)+y*m_sizeX);
        }
    }

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);


    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elements.size() * sizeof(GLuint), &m_elements[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexGrid.size() * sizeof(Vert), &m_vertexGrid[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, uv));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //std::cerr << "Terrain::generate " << GetGLErrorStr(glGetError()) << std::endl;


    m_terrainGenShader->bind();
    m_heightMap->bind(GL_TEXTURE1);
    m_terrainGenShader->setUniform("terrainImage", 1);
    m_terrainGenShader->setUniform("vertexBuffer", 0);
    m_terrainGenShader->setUniform("mapSize", glm::ivec2(m_heightMap->getWidth(), m_heightMap->getHeight()));

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_vbo);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_vbo);
    m_terrainGenShader->dispatch(glm::uvec3(m_vertexGrid.size()/32,1,1));
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void Terrain::draw(eng::rndr::Renderer *renderer)
{
    glBindVertexArray(m_vao);
    m_drawShader->bind();
    m_drawShader->setUniform("model", glm::mat4(1.));
    m_drawShader->setUniform("view", renderer->viewMat());
    m_drawShader->setUniform("projection", renderer->projMat());
    m_drawShader->setUniform("colourMap", 0);
    m_drawShader->setUniform("lightDir", glm::normalize(glm::vec3(0, .5, 1.)));
    m_drawShader->setUniform("lightCol", glm::vec3(1,.9,.85)*4.5);
    m_drawShader->setUniform("ambientCol", glm::vec3(.2,.3,.6)*.5);

    m_colMap->bind(GL_TEXTURE0);
    glDrawElements(GL_TRIANGLES, m_elements.size(), GL_UNSIGNED_INT, 0);
    glUseProgram(0);
    glBindVertexArray(0);
}
