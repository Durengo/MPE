#pragma once

#include "MPE/Base/_CORE.h"
#include "MPE/Base/Input/KeyCodes.h"
#include "MPE/Base/Input/MouseButtonCodes.h"

namespace MPE
{
    class MPE_API Input
    {
    private:
        static Input *SYS_Instance;

    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    public:
        inline static bool IsKeyPressed(int keycode) { return SYS_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return SYS_Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return SYS_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return SYS_Instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return SYS_Instance->GetMouseYImpl(); }
    };
}