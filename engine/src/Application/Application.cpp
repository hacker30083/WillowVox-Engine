#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Application/Window.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Texture.h>
#include <WillowVoxEngine/Rendering/Vertex.h>
#include <glm/glm.hpp>

namespace WillowVox
{
	Application* Application::app = nullptr;

	Application::Application()
	{
		app = this;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Load graphics API
		OpenGLGraphicsAPI openGLApi;
		openGLApi.Initialize();

		Window window;
		OpenGLGraphicsAPI::PostGladSetup();
		window.windowCloseEventDispatcher.RegisterListener([this](Event& event) {
			isRunning = false;
		});

		window.windowResizeEventDispatcher.RegisterListener([this](Event& event) {
			Logger::EngineLog("Window resized!\n");
		});

		// Load assets
		LoadAssets();

		input = new Input(window.GetWindow());
		window.SetInput(input);

		// Create world
		InitWorld();

		loadedWorld->Start();

		// Pre-game logic
		Start();

		while (isRunning)
		{
			// Calculate deltaTime
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			window.StartFrame();

			// Run game logic
			loadedWorld->Update();
			Update();

			// Render the game
			loadedWorld->Render();
			Render();

			window.EndFrame();
		}
	}
}