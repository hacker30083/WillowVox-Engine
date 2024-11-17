#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Core/Logger.h>

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
		// Test window code
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(600, 400, "Test", nullptr, nullptr);
		if (window == nullptr)
		{
			Logger::EngineLog("Failed to create window!\n");
			glfwTerminate();
			isRunning = false;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::EngineLog("Failed to initialize GLAD\n");
			isRunning = false;
		}

		glViewport(0, 0, 600, 400);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		while (!glfwWindowShouldClose(window) && isRunning)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			// Run game logic
			Update();

			// Render the game
			Render();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}
}