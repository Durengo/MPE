#pragma once

#include "_CORE.h"
#include "MPE/Events/Event.h"

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
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return SYS_DebugName; }
    };
}