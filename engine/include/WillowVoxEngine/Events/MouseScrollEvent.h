#pragma once

#include <WillowVoxEngine/Events/Event.h>

namespace WillowVox
{
    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float xOffset, float yOffset)
         : Event(Type::MouseScroll), xOffset(xOffset), yOffset(yOffset) {}

        std::string ToString() const override { return "MouseScrollEvent"; }

        float xOffset, yOffset;
    };
}