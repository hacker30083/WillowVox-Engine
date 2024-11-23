#pragma once

#include <WillowVoxEngine/Events/Event.h>

namespace WillowVox
{
    class MouseReleaseEvent : public Event
    {
    public:
        MouseReleaseEvent(int button)
         : Event(Type::MouseRelease), button(button) {}

        std::string ToString() const override { return "MouseReleaseEvent"; }

        int button;
    };
}