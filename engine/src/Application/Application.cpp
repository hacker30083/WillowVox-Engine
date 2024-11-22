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
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		OpenGLGraphicsAPI openGLApi;
		openGLApi.Initialize();
		
		Window window;
		window.windowEventDispatcher.RegisterListener(Event::Type::WindowClose, [this](Event& event) {
			isRunning = false;
		});

		window.windowEventDispatcher.RegisterListener(Event::Type::WindowResize, [this](Event& event) {
			Logger::EngineLog("Window resized!\n");
		});

		mainCamera = new Camera();

		// Pre-game logic
		Start();

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