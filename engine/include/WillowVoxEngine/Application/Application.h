#pragma once

#include <WillowVoxEngine/Rendering/Camera.h>

namespace WillowVox
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		Camera* mainCamera;

	protected:
		bool isRunning = true;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	// To be defined in client
	Application* CreateApplication();
}