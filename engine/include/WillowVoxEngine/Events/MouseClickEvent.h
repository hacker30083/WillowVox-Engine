#pragma once

#include <WillowVoxEngine/Events/Event.h>

namespace WillowVox
{
    class MouseClickEvent : public Event
    {
    public:
        MouseClickEvent(int button)
         : Event(Type::MouseClick), button(button) {}

        std::string ToString() const override { return "MouseClickEvent"; }

        int button;
    };
}