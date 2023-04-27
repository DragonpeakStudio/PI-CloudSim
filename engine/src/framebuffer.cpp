#include "framebuffer.h"
namespace eng::rndr
{
FrameBuffer::FrameBuffer(bool useDepth, std::unique_ptr<VFShaderProgram> shaderProgram) : m_fboShader(std::move(shaderProgram)), m_useDepth(useDepth)
{
}
FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void FrameBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if(m_useDepth)glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void FrameBuffer::init(unsigned int w, unsigned int h, GLint format)
{
    m_fboShader->load();

    m_fboTexture = std::make_unique<Texture2d>(nullptr, TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_RGBA, 4, format, GL_UNSIGNED_BYTE}, w, h);

    m_fboDepthTexture = std::make_unique<Texture2d>(nullptr, TextureInfo{GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, GL_DEPTH_COMPONENT, 1, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE}, w, h);

    if(m_fbo != 0)
    {
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fboTexture->id(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_fboDepthTexture->id(), 0);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::string err = "FrameBuffer::init unable to create framebuffer : ";
        GLenum e = glGetError();
        while(e != GL_NO_ERROR)
        {
            err += getGLErrorStr(e);
            e = glGetError();
        }
        throw std::runtime_error(err);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glGenVertexArrays(1, &m_fsqVao);
    glBindVertexArray(m_fsqVao);



    glGenBuffers(1, &m_fsqVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_fsqVbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &s_fsq[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Texture2d *FrameBuffer::frameBufferTexture()
{
	return m_fboTexture.get();
}

Texture2d *FrameBuffer::frameBufferDepthTexture()
{
	return m_fboDepthTexture.get();
}
void FrameBuffer::draw()
{
    glDisable(GL_DEPTH_TEST);
    m_fboShader->bind();
    m_fboShader->setUniform("image", 0);
    m_fboShader->setUniform("depthImage", 1);
    m_fboTexture->bind(GL_TEXTURE0);
    m_fboDepthTexture->bind(GL_TEXTURE1);

    glBindVertexArray(m_fsqVao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    if(m_useDepth)glEnable(GL_DEPTH_TEST);
}
void FrameBuffer::clear()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}