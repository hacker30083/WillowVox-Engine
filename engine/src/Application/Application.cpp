#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Application/Window.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/MeshRenderer.h>

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

		Shader shader("assets/vert.glsl", "assets/frag.glsl");
		shader.Use();
		shader.SetVec3("color", 0.5f, 1.0f, 0.5f);

		MeshRenderer mr(shader);

		Vertex vertices[] = {
			{ { -0.5f, -0.5f, 0.0f } },
			{ {  0.5f, -0.5f, 0.0f } },
			{ {  0.0f,  0.5f, 0.0f } }
		};

		Mesh* mesh = new Mesh();
		mesh->SetMeshData(vertices, 3);

		mr.SetMesh(mesh, true);

		while (isRunning)
		{
			window.StartFrame();

			// Run game logic
			Update();

			// Render the game
			Render();
			mr.Render();

			window.EndFrame();
		}
	}
}