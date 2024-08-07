#pragma once

#include "MPE/Core/_PTRS.h"
#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/VertexArray.h"
#include "MPE/Renderer/RenderSettings.h"

#include <glm/glm.hpp>

namespace MPE
{
class MPE_API RendererAPI
{
  public:
    enum class API
    {
        None = 0,
        OpenGL = 1,
        OpenGLES = 2
        // Direct3D
        // Vulcan
    };

    virtual void Init() = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    virtual void SetClearColor(const glm::vec4 &color) = 0;
    virtual void Clear() = 0;

    virtual void DrawIndexed(const REF<VertexArray> &vertexArray) = 0;
    virtual void DrawLines(const REF<VertexArray> &vertexArray, uint32_t vertexCount) = 0;

    virtual RenderSettings *GetSettings() = 0;

    inline static API GetGraphicsAPI()
    {
        if (!APISelected) throw std::runtime_error("No graphics API selected.");
        return GRAPHICS_API;
    }
    inline static void SetGraphicsAPI(API api)
    {
        GRAPHICS_API = api;
        APISelected = true;
    }

    static std::string APIToString(API api)
    {
        switch (api)
        {
            case API::None:
                return "None";
            case API::OpenGL:
                return "OpenGL";
            case API::OpenGLES:
                return "OpenGLES";
            default:
                MPE_ASSERT(false, "Unknown API.");
                return "Unknown";
        }
    }

  protected:
    inline static bool APISelected = false;

  private:
    static API GRAPHICS_API;
};
}