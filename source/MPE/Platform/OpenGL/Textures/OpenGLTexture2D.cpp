#include "MPE/MPEPCH.h"
#include "OpenGLTexture2D.h"
#include "MPE/Base/Log.h"
#include "MPE/Vendor/STB/stb_image.h"

#include <glad/glad.h>

namespace MPE
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string &filepath)
        : FILEPATH(filepath)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
        MPE_CORE_ASSERT(data, "FAILED TO LOAD IMAGE AS TEXTURE");
        WIDTH = width;
        HEIGHT = height;

        GLenum OpenGLInternalFormat = 0, OpenGLDataFormat = 0;
        switch (channels)
        {
        case 3:
            OpenGLInternalFormat = GL_RGB8;
            OpenGLDataFormat = GL_RGB;
            MPE_CORE_WARN("TEXTURE IMAGE FORMAT: RGB8/RGB");
            break;
        case 4:
            OpenGLInternalFormat = GL_RGBA8;
            OpenGLDataFormat = GL_RGBA;
            MPE_CORE_WARN("TEXTURE IMAGE FORMAT: RGB8/RGBA");
            break;
        default:
            MPE_CORE_ERROR("IMAGE FORMAT FOR TEXTURE IS INVALID");
            MPE_CORE_ASSERT(OpenGLInternalFormat || OpenGLDataFormat, "IMAGE FORMAT FOR TEXTURE IS NOT SUPPORTED");
            return;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &SYS_RENDERER_ID);
        glTextureStorage2D(SYS_RENDERER_ID, 1, OpenGLInternalFormat, WIDTH, HEIGHT);

        glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(SYS_RENDERER_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(SYS_RENDERER_ID, 0, 0, 0, WIDTH, HEIGHT, OpenGLDataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &SYS_RENDERER_ID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, SYS_RENDERER_ID);
    }
}