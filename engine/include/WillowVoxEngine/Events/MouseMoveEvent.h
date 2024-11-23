#pragma once

#include <WillowVoxEngine/Events/Event.h>

namespace WillowVox
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(float xOffset, float yOffset)
         : Event(Type::MouseMove), xOffset(xOffset), yOffset(yOffset) {}

        std::string ToString() const override { return "MouseMoveEvent"; }

        float xOffset, yOffset;
    };
}