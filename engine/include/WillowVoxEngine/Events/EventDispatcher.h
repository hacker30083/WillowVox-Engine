#pragma once

#include <functional>
#include <WillowVoxEngine/Events/Event.h>
#include <unordered_map>
#include <vector>

namespace WillowVox
{
    class EventDispatcher
    {
    public:
        // Register a listener for a specific event type
        void RegisterListener(Event::Type eventType, std::function<void(Event&)> listener);

        // Unregister all listeners for a specific event type
        void UnregisterAllListeners(Event::Type eventType);

        // Dispatch an event to all registered listeners
        void Dispatch(Event& event);

    private:
        // Store all the event listeners
        std::unordered_map<Event::Type, std::vector<std::function<void(Event&)>>> listeners;
    };
}