#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#pragma once
#include <unordered_map>
#include <string>
#include "texture.h"
namespace eng::rndr
{
struct Texture2dInfo
{
    GLint wrapS, wrapT, filterMin, filterMag, format, channels, internalFormat, type;
};
class Texture2d : public Texture
{
    public:
        Texture2d(const std::string &path, Texture2dInfo info);
        Texture2d(void *data, Texture2dInfo info, int width, int height);

        ~Texture2d();

		int getWidth() const;

		int getHeight() const;

    
    protected:
        void fromData(void *data);
        int m_width;
        int m_height;
        Texture2dInfo m_info;

};
}
#endif