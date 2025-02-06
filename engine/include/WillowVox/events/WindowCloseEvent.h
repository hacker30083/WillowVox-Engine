#pragma once

#include <WillowVox/events/Event.h>

namespace WillowVox
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() : Event(Type::WindowClose) {}

        std::string ToString() const override { return "WindowCloseEvent"; }
    };
}