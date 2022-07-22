#pragma once

#include "MPE/Platform/OpenGL/Textures/OpenGLTexture.h"
#include "MPE/Renderer/Textures/Texture2D.h"

namespace MPE
{
    class OpenGLTexture2D : public Texture2D
    {
    private:
        std::string FILEPATH;
        uint32_t WIDTH;
        uint32_t HEIGHT;
        uint32_t SYS_RENDERER_ID;

    public:
        OpenGLTexture2D(const std::string &filepath);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return WIDTH; };
        virtual uint32_t GetHeight() const override { return HEIGHT; };

        virtual void Bind(uint32_t slot = 0) const override;
    };
}