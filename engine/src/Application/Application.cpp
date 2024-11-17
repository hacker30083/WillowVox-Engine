#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		EventDispatcher testDispatcher;
		testDispatcher.RegisterListener(Event::Type::WindowClose, [this](Event& event) {
			isRunning = false;
			Logger::EngineLog("Window Closed\n");
		});

		while (isRunning)
		{
			// Run game logic
			Update();

			// Render the game
			Render();

			WindowCloseEvent windowCloseEvent;
			testDispatcher.Dispatch(windowCloseEvent);
		}
	}
}