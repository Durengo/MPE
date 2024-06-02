#pragma once

#include "MPE.h"

#include "MPE/Platform/OpenGL/Shaders/OpenGLShader.h"
#include "MPE/Renderer/Shaders/ShaderLibrary.h"

#include <imgui.h>
#include <string>

class TextureRectangleTest : public MPE::Layer
{
  public:
    TextureRectangleTest();

    virtual ~TextureRectangleTest() = default;

    virtual void OnUpdate(MPE::Time deltatime) override;

    virtual void OnImGuiRender() override;

    virtual void OnEvent(MPE::Event &event) override;

    bool OnKeyPressedEvent(MPE::KeyPressedEvent &event);

  private:
    MPE::SCOPE<std::string> m_LayerName;

    // Scene
    float CLEAR_COLOR[4];

    // Camera
    MPE::StaticOrthographicCamera SYS_CAMERA_CONTROLLER;

    // Rectangle
    MPE::REF<MPE::Shader> SYS_Shader;
    MPE::REF<MPE::VertexArray> SYS_VertexArray;

    glm::vec3 RECTANGLE_POSITION;
    float RECTANGLE_SCALE_FACTOR;
    glm::vec3 RECTANGLE_VECTOR_SCALE;
    glm::mat4 RECTANGLE_SCALE;

    // Shader Library
    MPE::ShaderLibrary SYS_SHADER_LIBRARY;

    // TEXTURES;
    MPE::REF<MPE::Texture2D> TEST_TEXTURE;
};