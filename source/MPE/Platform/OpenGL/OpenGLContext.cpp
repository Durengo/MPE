#include "MPE/MPEPCH.h"
#include "OpenGLContext.h"
#include "MPE/Base/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MPE
{
    OpenGLContext::OpenGLContext(GLFWwindow *window)
        : SYS_Window(window)
    {
        MPE_CORE_ASSERT(SYS_Window, "WINDOW IS NULL.")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(SYS_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        MPE_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD.")

        MPE_CORE_INFO("OpenGL Info:");
        #ifdef MPE_ENABLE_ASSERTS

            int OpenGLVersionMajor;
            int OpenGLVersionMinor;
            glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersionMajor);
            glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersionMinor);

            MPE_CORE_ASSERT(OpenGLVersionMajor > 4 || (OpenGLVersionMajor == 4 && OpenGLVersionMinor >= 6), "MPE REQUIRES OPENGL VERSION 4.6 OR GREATER.");

            MPE_CORE_INFO("OpenGL Version: {0}.{1}", OpenGLVersionMajor, OpenGLVersionMinor);

        #endif
        MPE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
        MPE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        MPE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
        MPE_CORE_INFO("Hardcode shader type limit: {0}", OPENGL_SHADER_TYPE_AMOUNT);
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(SYS_Window);
    }
}