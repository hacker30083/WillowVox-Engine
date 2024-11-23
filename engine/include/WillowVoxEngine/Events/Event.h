#pragma once

#include <string>

namespace WillowVox
{
    class Event
    {
    public:
        enum class Type
        {
            None = 0,
            KeyPress, KeyRelease,
            MouseMove, MouseClick, MouseRelease, MouseScroll,
            WindowResize, WindowClose
        };

        Event(Type type) : type(type), handled(false) {}

        Type GetType() const { return type; }
        bool IsHandled() const { return handled; }
        void MarkHandled() { handled = true; }

        virtual std::string ToString() const { return "Event"; }

    private:
        Type type;
        bool handled;
    };
}