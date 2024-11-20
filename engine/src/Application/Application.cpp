#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Application/Window.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Texture.h>
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
		mainCamera = new Camera();

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
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f } },
			{ {  0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f } },
			{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f } },
			{ {  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f } },
		};
	
		uint32_t indices[] = {
			0, 1, 3,
			0, 2, 3
		};

		Mesh* mesh = new Mesh();
		mesh->SetMeshData(vertices, 4, indices, 6);

		mr.SetMesh(mesh, true);

		Texture tex("assets/grass_block_side.png");
		tex.BindTexture(Texture::TEX00);

		while (isRunning)
		{
			window.StartFrame();

			// Run game logic
			Update();

			// Render the game
			Render();
			glm::mat4 view = mainCamera->GetViewMatrix();
			glm::mat4 projection = glm::perspective(glm::radians(mainCamera->Zoom), 600.0f / 400.0f, 0.1f, 1000.0f);
			shader.Use();
			shader.SetMat4("view", view);
			shader.SetMat4("projection", view);
			shader.SetVec3("model", 0, 0, 0);

			mr.Render();

			window.EndFrame();
		}
	}
}