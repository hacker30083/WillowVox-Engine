#pragma once

#include <WillowVox/events/Event.h>
#include <WillowVox/input/Key.h>

namespace WillowVox
{
    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(Key key) 
            : Event(Type::KeyRelease), m_key(key) {}

        std::string ToString() const override { return "KeyReleaseEvent"; }
    
        Key m_key;
    };
}