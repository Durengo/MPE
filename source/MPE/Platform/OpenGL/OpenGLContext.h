#pragma once

#include "MPE/Renderer/GraphicalContext.h"

struct GLFWwindow;

namespace MPE
{
    class OpenGLContext : public GraphicalContext
    {
    private:
        GLFWwindow *SYS_Window;

    public:
        OpenGLContext(GLFWwindow *window);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    };
}