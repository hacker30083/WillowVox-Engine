

#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Application/Window.h>

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
		Window window;
		window.windowCloseDispatcher.RegisterListener(Event::Type::WindowClose, [this](Event& event) {
			isRunning = false;
		});

		while (isRunning)
		{
			window.StartFrame();

			// Run game logic
			Update();

			// Render the game
			Render();

			window.EndFrame();
		}
	}
}