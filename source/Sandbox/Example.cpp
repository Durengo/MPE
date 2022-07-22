#include "MPE/MPE.h"

// TEMP
#include "imgui.h"
#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
// TEMP
class TestLayer : public MPE::Layer
{
private:
public:
    TestLayer()
        : Layer("Test")
    {
    }

    virtual void OnUpdate(MPE::_TIME deltatime) override
    {
    }

    virtual void OnImGuiRender() override
    {
    }

    virtual void OnEvent(MPE::Event &event) override
    {
    }
};

class Example : public MPE::App
{
public:
    Example()
    {
        PushLayer(new TestLayer());
    }

    ~Example()
    {
    }
};

MPE::App *MPE::CreateApp()
{
    return new Example();
}