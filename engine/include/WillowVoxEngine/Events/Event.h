#pragma once

#include <string>
#include <functional>

namespace WillowVox
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize,
		KeyPress, KeyRelease,
		MouseButtonPress, MouseButtonRelease, MouseMove
	};

	class Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const { return "Event"; }
		bool Handled = false;

		static EventType GetStaticType() { return EventType::None; }
	};
}