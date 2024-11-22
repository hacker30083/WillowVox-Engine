#include <WillowVoxEngine/Application/Window.h>

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Events/WindowResizeEvent.h>

namespace WillowVox
{
    Window::Window()
    {
        // Set window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(600, 400, "Test", nullptr, nullptr);
		if (window == nullptr)
		{
			Logger::EngineLog("Failed to create window!\n");
			glfwTerminate();
            WindowCloseEvent e;
            windowEventDispatcher.Dispatch(e);
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::EngineLog("Failed to initialize GLAD\n");
            WindowCloseEvent e;
            windowEventDispatcher.Dispatch(e);
		}

		glViewport(0, 0, 600, 400);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glfwSetWindowUserPointer(window, static_cast<void*>(this));
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            glViewport(0, 0, width, height);
            WindowResizeEvent e(width, height);
            self->windowEventDispatcher.Dispatch(e);
        });
    }

    Window::~Window()
    {

    }

    void Window::StartFrame()
    {
        if (glfwWindowShouldClose(window))
        {
            WindowCloseEvent e;
            windowEventDispatcher.Dispatch(e);
        }

        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::EndFrame()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}