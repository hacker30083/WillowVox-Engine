#pragma once

#include <WillowVoxEngine/Rendering/Camera.h>
#include <WillowVoxEngine/Input/Input.h>

namespace WillowVox
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		Camera* mainCamera;
		Input* input;
		float deltaTime;

	protected:
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		bool isRunning = true;

	private:
		float lastFrame = 0;
	};

	// To be defined in client
	Application* CreateApplication();
}