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
            MouseMove, MouseClick,
            WindowResize, WindowClose
        };

        Event(Type type) : type(type), handled(false) {}

        Type GetType() const { return type; }
        bool IsHandled() const { return handled; }
        void MarkHandled() { handled = true; }

        virtual std::string toString() const { return "Event"; }

    private:
        Type type;
        bool handled;
    };
}