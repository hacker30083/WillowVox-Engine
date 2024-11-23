#pragma once

#include <WillowVoxEngine/Rendering/Camera.h>
#include <WillowVoxEngine/Input/Input.h>
#include <WillowVoxEngine/World/World.h>

namespace WillowVox
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		Input* input;
		float deltaTime;

	protected:
		virtual void LoadAssets() = 0;
		virtual void InitWorld() = 0;

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		bool isRunning = true;
		
		World* loadedWorld;

	private:

		float lastFrame = 0;
	};

	// To be defined in client
	Application* CreateApplication();
}