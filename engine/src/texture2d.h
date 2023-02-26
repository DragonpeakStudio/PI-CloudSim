#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#pragma once
#include <unordered_map>
#include <string>
#include "texture.h"
namespace eng::rndr
{

class Texture2d : public Texture
{
    public:
        Texture2d(const std::string &path, TextureInfo info);
        Texture2d(void *data, TextureInfo info, int width, int height);

        ~Texture2d();

		int getWidth() const;

		int getHeight() const;

    
    protected:
        void fromData(void *data);
        int m_width;
        int m_height;
        TextureInfo m_info;

};
}
#endif