#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <WillowVoxEngine/Events/EventDispatcher.h>
#include <WillowVoxEngine/Events/WindowCloseEvent.h>

namespace WillowVox
{
    class Window
    {
    public:
        Window();
        ~Window();

        void StartFrame();
        void EndFrame();

        EventDispatcher windowCloseDispatcher;

    private:
        GLFWwindow* window;
    };
}