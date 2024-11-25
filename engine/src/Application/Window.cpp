#include <WillowVoxEngine/Application/Window.h>

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Events/MouseScrollEvent.h>
#include <WillowVoxEngine/Events/KeyPressEvent.h>
#include <WillowVoxEngine/Events/KeyReleaseEvent.h>
#include <WillowVoxEngine/Events/MouseMoveEvent.h>
#include <WillowVoxEngine/Events/MouseClickEvent.h>
#include <WillowVoxEngine/Events/MouseReleaseEvent.h>

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
            windowCloseEventDispatcher.Dispatch(e);
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::EngineLog("Failed to initialize GLAD\n");
            WindowCloseEvent e;
            windowCloseEventDispatcher.Dispatch(e);
		}

		glViewport(0, 0, 600, 400);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Callbacks
        glfwSetWindowUserPointer(window, static_cast<void*>(this));

        // Window callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            glViewport(0, 0, width, height);
            WindowResizeEvent e(width, height);
            self->windowResizeEventDispatcher.Dispatch(e);
        });

        // Input callbacks
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            
            if (action == GLFW_PRESS)
            {
                KeyPressEvent e((Key)key);
                self->input->keyPressEventDispatcher.Dispatch(e);
            }
            else if (action == GLFW_RELEASE)
            {
                KeyReleaseEvent e((Key)key);
                self->input->keyReleaseEventDispatcher.Dispatch(e);
            }
		});

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
			auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));

            MouseScrollEvent e(xoffset, yoffset);
            self->input->mouseScrollEventDispatcher.Dispatch(e);
		});

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            MouseMoveEvent e(xpos - self->lastMouseX, self->lastMouseY - ypos);
            self->lastMouseX = xpos;
            self->lastMouseY = ypos;
            self->input->mouseMoveEventDispatcher.Dispatch(e);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            if (action == GLFW_PRESS)
            {
                MouseClickEvent e(button);
                self->input->mouseClickEventDispatcher.Dispatch(e);
            }
            else
            {
                MouseReleaseEvent e(button);
                self->input->mouseReleaseEventDispatcher.Dispatch(e);
            }
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
            windowCloseEventDispatcher.Dispatch(e);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EndFrame()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Window::SetInput(Input* input) { this->input = input; }

    GLFWwindow* Window::GetWindow() { return window; }
}