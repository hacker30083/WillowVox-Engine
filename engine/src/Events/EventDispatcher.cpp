#include <WillowVoxEngine/Events/EventDispatcher.h>

namespace WillowVox
{
    void EventDispatcher::RegisterListener(Event::Type eventType, Listener listener)
    {
        listeners[eventType].push_back(listener);
    }

    void EventDispatcher::UnregisterAllListeners(Event::Type eventType)
    {
        listeners.erase(eventType);
    }

    void EventDispatcher::Dispatch(Event& event)
    {
        auto it = listeners.find(event.GetType());
        if (it != listeners.end())
        {
            for (auto& l : it->second)
            {
                l(event);

                // Stop propagation if event is marked as handled
                if (event.IsHandled())
                    break;
            }
        }
    }
}