#pragma once

#include "MPE/Base/Layer.h"
// #include "MPE/Events/EventKey.h"
// #include "MPE/Events/EventMouse.h"
// #include "MPE/Events/EventApp.h"

namespace MPE
{
    class MPE_API ImGuiLayer : public Layer
    {
    private:
        float SYS_Time = 0.0f;

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    };
}