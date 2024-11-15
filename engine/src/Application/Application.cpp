#include <WillowVoxEngine/Application/Application.h>

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
}