#pragma once

#include "MPE/Base/_TIME.h"
#include "MPE/Base/Events/Event.h"

namespace MPE
{
    class MPE_API Layer
    {
    protected:
        std::string SYS_DebugName;

    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(_TIME deltatime) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return SYS_DebugName; }
    };
}