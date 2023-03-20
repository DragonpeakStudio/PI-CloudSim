#include "cloudvolumerenderer.h"

CloudVolumeRenderer::CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox) : CloudRenderer(bbox), m_drawShader("../resources/shaders/basic.vert", "../resources/shaders/volumeclouds.frag")
{
    static const glm::vec2 fsq[] = {glm::vec2(-1.,-1.),
		glm::vec2(1.,1.),
		glm::vec2(-1.,1.),
		glm::vec2(-1.,-1.),
		glm::vec2(1.,-1.),
		glm::vec2(1.,1.)};
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &fsq[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_drawShader.load();
}
CloudVolumeRenderer::~CloudVolumeRenderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void CloudVolumeRenderer::draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer)//TODO offscreen draw to allow lowres volume rendering
{
    glm::ivec4 viewport; 
    glGetIntegerv( GL_VIEWPORT, &viewport.x );
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(m_vao);
    m_drawShader.bind();
    m_drawShader.setUniform("densityField", 0);
    m_drawShader.setUniform("bboxMin", m_bbox.first);
    m_drawShader.setUniform("bboxMax", m_bbox.second);
    m_drawShader.setUniform("camPos", glm::inverse(renderer.viewMat())[3]);
    auto vm = renderer.viewMat();
    vm[3] = glm::vec4(0,0,0,vm[3].w);//Bodge to remove the position component of view matrix, avoiding offset of ray dir
    m_drawShader.setUniform("invProjView",glm::inverse(renderer.projMat()*vm));
    m_drawShader.setUniform("viewport", viewport);
    densityField.bind(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);  

}
void CloudVolumeRenderer::drawUI()
{
}