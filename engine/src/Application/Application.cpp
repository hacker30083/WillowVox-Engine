#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowEvents.h>

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
		int a = 3;
		while (isRunning)
		{
			//WindowCloseEvent closeEvent;
			//OnEvent(closeEvent);

			// Run game logic
			Update();

			// Render the game
			Render();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event)
		{
			isRunning = false;
			return true;
		});
	}
}