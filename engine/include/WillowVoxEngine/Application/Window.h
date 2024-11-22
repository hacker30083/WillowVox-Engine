#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <WillowVoxEngine/Events/EventDispatcher.h>
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

        void SetInput(Input* input);
        GLFWwindow* GetWindow();

        EventDispatcher windowEventDispatcher;

    private:
        GLFWwindow* window;
        Input* input;
    };
}