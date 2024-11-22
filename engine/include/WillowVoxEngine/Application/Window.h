#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <WillowVoxEngine/Events/EventDispatcher.h>

namespace WillowVox
{
    class Window
    {
    public:
        Window();
        ~Window();

        void StartFrame();
        void EndFrame();

        EventDispatcher windowEventDispatcher;

    private:
        GLFWwindow* window;
    };
}