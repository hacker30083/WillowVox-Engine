#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>
#include <WillowVoxEngine/Events/WindowResizeEvent.h>
#include <WillowVoxEngine/Input/Input.h>

namespace WillowVox
{
    class Window
    {
    public:
        Window();
        ~Window();

        void StartFrame();
        void EndFrame();

        void SetBackgroundColor(float r, float g, float b);

        void SetInput(Input* input);
        GLFWwindow* GetWindow();

        EventDispatcher<WindowCloseEvent> windowCloseEventDispatcher;
        EventDispatcher<WindowResizeEvent> windowResizeEventDispatcher;

    private:
        GLFWwindow* window;
        Input* input;

        float lastMouseX, lastMouseY;
    };
}