#pragma once

#include "Event.h"
#include <sstream>

namespace WillowVox
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EventType GetEventType() const override { return EventType::WindowClose; }
		static EventType GetStaticType() { return EventType::WindowClose; }

		std::string ToString() const override { return "WindowCloseEvent"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height) : m_Width(width), m_Height(height) {}

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }

		EventType GetEventType() const override { return EventType::WindowResize; }
		static EventType GetStaticType() { return EventType::WindowResize; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		int m_Width, m_Height;
	};
}