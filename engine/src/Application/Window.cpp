#include <WillowVoxEngine/Application/Window.h>

#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
    Window::Window()
    {
        // Test window code
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(600, 400, "Test", nullptr, nullptr);
		if (window == nullptr)
		{
			Logger::EngineLog("Failed to create window!\n");
			glfwTerminate();
            WindowCloseEvent e;
            windowCloseDispatcher.Dispatch(e);
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::EngineLog("Failed to initialize GLAD\n");
            WindowCloseEvent e;
            windowCloseDispatcher.Dispatch(e);
		}

		glViewport(0, 0, 600, 400);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Window::~Window()
    {
		glfwTerminate();
    }

    void Window::StartFrame()
    {
        if (glfwWindowShouldClose(window))
        {
            WindowCloseEvent e;
            windowCloseDispatcher.Dispatch(e);
        }

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::EndFrame()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}