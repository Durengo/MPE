#pragma once

#include "MPE/Renderer/RendererAPI.h"

namespace MPE
{
    class RenderPrimitive
    {
    private:
        static RendererAPI *SYS_API;

    public:
        inline static void Init()
        {
            SYS_API->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            SYS_API->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4 &color)
        {
            SYS_API->SetClearColor(color);
        }
        inline static void Clear()
        {
            SYS_API->Clear();
        }

        inline static void DrawIndexed(const REF<VertexArray> &vertexArray)
        {
            SYS_API->DrawIndexed(vertexArray);
        }
    };
}