#pragma once

#include <WillowVoxEngine/Events/Event.h>
#include <WillowVoxEngine/Input/Input.h>

namespace WillowVox
{
    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(Key key)
         : Event(Type::KeyPress), key(key) {}

        std::string ToString() const override { return "KeyPressEvent"; }

        Key key;
    };
}