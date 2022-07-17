//#include <MPE.h>
//#include <MPEPCH.h>
#include "MPE/MPE.h"
#include "imgui.h"

class TestLayer : public MPE::Layer
{
public:
    TestLayer()
        : Layer("Test") {}

    virtual void OnUpdate() override
    {
        // MPE_INFO("TestLayer::Update");
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("TEST");
        ImGui::Text("HELLO ENGINE");
        ImGui::End();
        ImGui::Begin("TEST2");
        ImGui::Text("HELLO ENGINE 2");
        ImGui::End();
    }

    virtual void OnEvent(MPE::Event &event) override
    {
        MPE_TRACE("{0}", event);
        // if (event.GetEventType() == MPE::EventType::KeyPressed)
        // {
        // 	MPE::KeyPressedEvent& e = (MPE::KeyPressedEvent&)event;
        // 	if (e.GetKeyCode() == MPE_KEY_ESCAPE)
        // 		MPE_TRACE("ESC key is pressed (event)!");
        // 	//MPE_TRACE("{0}", (char)e.GetKeyCode());
        // }
    }
};

class Sandbox : public MPE::App
{
public:
    Sandbox()
    {
        PushLayer(new TestLayer());
    }

    ~Sandbox()
    {
    }
};

MPE::App *MPE::CreateApp()
{
    return new Sandbox();
}