#pragma once

#include <WillowVoxEngine/Events/Event.h>
#include <WillowVoxEngine/Input/Key.h>

namespace WillowVox
{
    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(Key key)
         : Event(Type::KeyRelease), key(key) {}

        std::string ToString() const override { return "KeyReleaseEvent"; }

        Key key;
    };
}