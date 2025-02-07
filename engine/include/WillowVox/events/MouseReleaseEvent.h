#pragma once

#include <WillowVox/events/Event.h>

namespace WillowVox
{
    class MouseReleaseEvent : public Event
    {
    public:
        MouseReleaseEvent(int button) 
            : Event(Type::MouseRelease), m_button(button) {}

        std::string ToString() const override { return "MouseReleaseEvent"; }
    
        int m_button;
    };
}