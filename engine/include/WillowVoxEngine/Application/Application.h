#pragma once

#include "../Events/Event.h"

namespace WillowVox
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		virtual void OnEvent(Event& e);

	protected:
		bool isRunning = true;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	// To be defined in client
	Application* CreateApplication();
}