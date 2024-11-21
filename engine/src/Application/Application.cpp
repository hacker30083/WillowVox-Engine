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
#include <iostream>

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

		MeshRenderer<Vertex> mr(shader);

		Vertex vertices[] = {
			{ { -1.0f, -1.0f, -5.0f }, { 0.0f, 0.0f } },
			{ {  1.0f, -1.0f, -5.0f }, { 1.0f, 0.0f } },
			{ { -1.0f,  1.0f, -5.0f }, { 0.0f, 1.0f } },
			{ {  1.0f,  1.0f, -5.0f }, { 1.0f, 1.0f } },
		};
	
		uint32_t indices[] = {
			0, 1, 3,
			0, 2, 3
		};

		Mesh<Vertex>* mesh = new Mesh<Vertex>();
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
			glm::mat4 projection = mainCamera->GetProjectionMatrix();
			shader.Use();
			shader.SetMat4("view", view);
			shader.SetMat4("projection", projection);
			shader.SetVec3("model", 0, 0, 0);

			mr.Render();

			window.EndFrame();
		}
	}
}