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
        using Listener = std::function<void(Event&)>;

        // Register a listener for a specific event type
        void RegisterListener(Event::Type eventType, Listener listener);

        // Unregister all listeners for a specific event type
        void UnregisterAllListeners(Event::Type eventType);

        // Dispatch an event to all registered listeners
        void Dispatch(Event& event);

    private:
        // Store all the event listeners
        std::unordered_map<Event::Type, std::vector<Listener>> listeners;
    };
}