#pragma once

#include "MPE/Renderer/Textures/Texture.h"

namespace MPE
{
    class Texture2D : public Texture
    {
    private:
    public:
        static REF<Texture2D> Create(uint32_t width, uint32_t height);
        static REF<Texture2D> Create(const std::string &filepath);
    };
}