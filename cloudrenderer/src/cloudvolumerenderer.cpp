#include "cloudvolumerenderer.h"

CloudVolumeRenderer::CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox, std::weak_ptr<OutdoorLighting> lighting) : CloudRenderer(bbox, lighting), m_drawShader("../resources/shaders/basic.vert", "../resources/shaders/volumeclouds.frag"),
m_noiseKernal(nullptr, eng::rndr::TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 4, GL_RGBA16F, GL_FLOAT}, 64,64,64), m_noiseKernalGenerator("../resources/shaders/generatenoisekernal.comp"), m_slicer(m_noiseKernal)
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
    m_noiseKernalGenerator.load();
    generateNoiseKernal();
}
CloudVolumeRenderer::~CloudVolumeRenderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
void CloudVolumeRenderer::draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer)//TODO offscreen draw to allow lowres volume rendering
{
    m_time+=1;
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

    auto lighting = m_lighting.lock();
    m_drawShader.setUniform("sunDir", lighting->sunDir());
    m_drawShader.setUniform("sunCol", lighting->sunCol()*m_sunBrightness);
    m_drawShader.setUniform("ambientCol", lighting->ambientCol()*m_ambientBrightness);
    m_drawShader.setUniform("lightStepSize", m_lightStepSize);
    m_drawShader.setUniform("lightFar", m_lightFar);
    m_drawShader.setUniform("lightDensMult", m_lightDensMult);
    m_drawShader.setUniform("stepSize", m_stepSize);
    m_drawShader.setUniform("time", m_time);


    densityField.bind(GL_TEXTURE0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);  

}
void CloudVolumeRenderer::drawUI()
{
    ImGui::Begin("Cloud Rendering");

    ImGui::SliderFloat("Sun Mult", &m_sunBrightness, 0., 1.);
    ImGui::SliderFloat("Ambient Mult", &m_ambientBrightness, 0., 1.);
    ImGui::SliderFloat("Step Size", &m_stepSize, 0., 100.);
    ImGui::SliderFloat("Light Step Size", &m_lightStepSize, 0., 10.);
    ImGui::SliderFloat("Light Far", &m_lightFar, 0., 10.);
    ImGui::SliderFloat("Light Dens Mult", &m_lightDensMult, 0., 5.);
    ImGui::SliderInt("Slice", &m_debugSlice, 0, m_noiseKernal.depth());
    m_slicer.update(m_debugSlice);
    ImGui::Image((void*)(intptr_t)m_slicer.getSlice()->id(), {(float)128.f, (float)128.f});

    ImGui::End();
}

void CloudVolumeRenderer::generateNoiseKernal()
{
    glBindImageTexture(1, m_noiseKernal.id(), 0, false, 0, GL_READ_WRITE, GL_RGBA16F);
    m_noiseKernalGenerator.dispatch(glm::uvec3(m_noiseKernal.width()/8, m_noiseKernal.height()/8, m_noiseKernal.depth()/8));
}
