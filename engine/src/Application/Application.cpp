

#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Application/Window.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Rendering/Shader.h>

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

		float vertices[] = {
			-.5f, -.5f,
			 .5f, -.5f,
			 .0f,  .5f
		};

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);  
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		while (isRunning)
		{
			window.StartFrame();

			// Run game logic
			Update();

			// Render the game
			Render();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			window.EndFrame();
		}
	}
}