#pragma once

#include <WillowVox/events/Event.h>

namespace WillowVox
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(float xOffset, float yOffset) 
            : Event(Type::MouseMove), m_xOffset(xOffset), m_yOffset(yOffset) {}

        std::string ToString() const override { return "MouseMoveEvent"; }
    
        float m_xOffset, m_yOffset;
    };
}