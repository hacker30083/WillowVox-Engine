#pragma once

#include <WillowVox/events/Event.h>

namespace WillowVox
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int newWidth, int newHeight) 
         : Event(Type::WindowResize), newWidth(newWidth), newHeight(newHeight) {}

        std::string ToString() const override { return "WindowResizeEvent"; }

        int newWidth;
        int newHeight;
    };
}