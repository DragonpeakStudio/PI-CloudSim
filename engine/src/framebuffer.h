#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <memory>
#include <GL/glew.h>
#include "vfshaderprogram.h"
#include "glutil.h"
#include "texture2d.h"
namespace eng::rndr
{

class FrameBuffer
{
    public:
        FrameBuffer(bool useDepth, std::unique_ptr<VFShaderProgram> shaderProgram);
        ~FrameBuffer();
        void bind();
        void init(unsigned int w, unsigned int h, GLint format);
        void draw();
        void clear();

        Texture2d *frameBufferTexture();
		Texture2d *frameBufferDepthTexture();
        inline static const glm::vec2 s_fsq[] = {glm::vec2(-1.,-1.),
		glm::vec2(1.,1.),
		glm::vec2(-1.,1.),
		glm::vec2(-1.,-1.),
		glm::vec2(1.,-1.),
		glm::vec2(1.,1.)};


    private:
        GLuint m_fbo;
        std::unique_ptr<ShaderProgram> m_fboShader;
        std::unique_ptr<Texture2d> m_fboTexture;
        std::unique_ptr<Texture2d> m_fboDepthTexture;
        bool m_useDepth;

        GLuint m_fsqVao = 0;
        GLuint m_fsqVbo = 0;


};
}
#endif // FRAMEBUFFER_H
