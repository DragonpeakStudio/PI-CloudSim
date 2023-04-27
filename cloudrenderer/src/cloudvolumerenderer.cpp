#include "cloudvolumerenderer.h"

CloudVolumeRenderer::CloudVolumeRenderer(std::pair<glm::vec3, glm::vec3> bbox, std::weak_ptr<OutdoorLighting> lighting) : CloudRenderer(bbox, lighting), m_drawShader("../resources/shaders/basic.vert", "../resources/shaders/volumeclouds.frag"),
m_frameBuffer(std::make_unique<eng::rndr::FrameBuffer>(false, std::make_unique<eng::rndr::VFShaderProgram>("../resources/shaders/basic.vert", "../resources/shaders/cloudcomp.frag")))
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
    glGetIntegerv( GL_VIEWPORT, &m_origViewport.x );
    m_scaledViewport = glm::ivec4(m_origViewport.x, m_origViewport.y, m_origViewport.z*m_cloudResMult, m_origViewport.w*m_cloudResMult);
    m_frameBuffer->init(m_scaledViewport.z, m_scaledViewport.w, GL_RGBA);
    m_lastFrame = std::make_unique<eng::rndr::Texture2d>(nullptr, m_frameBuffer->frameBufferTexture()->info(), m_scaledViewport.z, m_scaledViewport.w);

}
CloudVolumeRenderer::~CloudVolumeRenderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
void CloudVolumeRenderer::draw(eng::rndr::Texture3d &densityField, eng::rndr::Renderer &renderer)
{
    glMemoryBarrier(GL_FRAMEBUFFER_BARRIER_BIT);
    m_frameBuffer->bind();
    glCopyImageSubData(m_frameBuffer->frameBufferTexture()->id(), GL_TEXTURE_2D, 0, 0, 0, 0, m_lastFrame->id(), GL_TEXTURE_2D, 0, 0, 0, 0, m_lastFrame->width(), m_lastFrame->height(), 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(m_scaledViewport.x, m_scaledViewport.y,m_scaledViewport.z,m_scaledViewport.w);
    m_time+=1;
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(m_vao);
    m_drawShader.bind();
    m_drawShader.setUniform("densityField", 0);
    m_drawShader.setUniform("sceneDepth", 1);
    m_drawShader.setUniform("lastFrame", 2);
    m_drawShader.setUniform("bboxMin", m_bbox.first);
    m_drawShader.setUniform("bboxMax", m_bbox.second);
    m_drawShader.setUniform("camPos", glm::inverse(renderer.viewMat())[3]);
    auto vm = renderer.viewMat();
    vm[3] = glm::vec4(0,0,0,vm[3].w);//Bodge to remove the position component of view matrix, avoiding offset of ray dir
    m_drawShader.setUniform("invProjView",glm::inverse(renderer.projMat()*vm));
    m_drawShader.setUniform("viewport", m_scaledViewport);
    auto lighting = m_lighting.lock();
    m_drawShader.setUniform("sunDir", lighting->sunDir());
    m_drawShader.setUniform("sunCol", lighting->sunCol()*m_sunBrightness);
    m_drawShader.setUniform("ambientCol", lighting->ambientCol()*m_ambientBrightness);
    m_drawShader.setUniform("lightStepSize", m_lightStepSize);
    m_drawShader.setUniform("lightFar", m_lightFar);
    m_drawShader.setUniform("lightDensMult", m_lightDensMult);
    m_drawShader.setUniform("stepSize", m_stepSize);
    m_drawShader.setUniform("time", m_time);
    m_drawShader.setUniform("densMult", m_densMult);
    m_drawShader.setUniform("nearPlane", renderer.nearPlane());
    m_drawShader.setUniform("farPlane", renderer.farPlane());
    m_drawShader.setUniform("lastFrameBlend", m_lastFrameBlend);
    densityField.bind(GL_TEXTURE0);
    renderer.frameBuffer().frameBufferDepthTexture()->bind(GL_TEXTURE1);
    m_lastFrame->bind(GL_TEXTURE2);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(0);
    glBindVertexArray(0);
    glViewport(m_origViewport.x, m_origViewport.y,m_origViewport.z,m_origViewport.w);
    renderer.frameBuffer().bind();
    m_frameBuffer->draw();
    glEnable(GL_DEPTH_TEST);  

}


void CloudVolumeRenderer::drawUI()
{
    ImGui::Begin("Cloud Rendering");

    ImGui::SliderFloat("Sun Mult", &m_sunBrightness, 0., 3.);
    ImGui::SliderFloat("Ambient Mult", &m_ambientBrightness, 0., 3.);
    ImGui::SliderFloat("Dens Mult", &m_densMult, 0., 4.);

    ImGui::SliderFloat("Step Size", &m_stepSize, .5, 100.);
    ImGui::SliderFloat("Light Step Size", &m_lightStepSize, .2, 20.);
    ImGui::SliderFloat("Light Far", &m_lightFar, 0., 50.);
    ImGui::SliderFloat("Light Dens Mult", &m_lightDensMult, 0., 15.);
    ImGui::SliderFloat("Light Dens Mult", &m_lightDensMult, 0., 15.);
    if(ImGui::SliderFloat("Cloud Render Scale", &m_cloudResMult, 0., 1.))
    {
        glGetIntegerv( GL_VIEWPORT, &m_origViewport.x );
        m_scaledViewport = glm::ivec4(m_origViewport.x, m_origViewport.y, m_origViewport.z*m_cloudResMult, m_origViewport.w*m_cloudResMult);
        m_frameBuffer->init(m_scaledViewport.z, m_scaledViewport.w, GL_RGBA);
        m_lastFrame = std::make_unique<eng::rndr::Texture2d>(nullptr, m_frameBuffer->frameBufferTexture()->info(), m_scaledViewport.z, m_scaledViewport.w);

    }

    ImGui::SliderFloat("Last Frame Blend", &m_lastFrameBlend, 0., 1.);


    ImGui::End();
}
