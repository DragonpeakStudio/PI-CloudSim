#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <GL/glew.h>
namespace eng::rndr
{
struct TextureInfo
{
    GLint wrapS, wrapT, filterMin, filterMag, format, channels, internalFormat, type;
};
class Texture
{
    public:
        Texture();
        virtual ~Texture();

        GLuint id() const;
        void bind(GLenum unit);
        
    
    protected:
        GLuint m_id;
};
}
#endif