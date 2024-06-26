#pragma once

#include "MPE/Events/Event.h"

namespace MPE
{
class MPE_API MouseMovedEvent : public Event
{
  private:
    float MouseX, MouseY;

  public:
    MouseMovedEvent(float x, float y);

    inline float GetX() const { return MouseX; }
    inline float GetY() const { return MouseY; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MPE_API MouseScrolledEvent : public Event
{
  private:
    float XOffset, YOffset;

  public:
    MouseScrolledEvent(float xoffset, float yoffset);
    inline float GetXOffset() const { return XOffset; }
    inline float GetYOffset() const { return YOffset; }

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MPE_API MouseButtonEvent : public Event
{
  protected:
    MouseButtonEvent(int button);

    int Button;

  public:
    inline int GetMouseButton() const { return Button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MPE_API MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MPE_API MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button);

    std::string ToString() const override;

    EVENT_CLASS_TYPE(MouseButtonReleased)
};
}