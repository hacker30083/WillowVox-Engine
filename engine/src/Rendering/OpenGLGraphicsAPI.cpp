#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace WillowVox
{
    OpenGLGraphicsAPI::~OpenGLGraphicsAPI()
    {
        glfwTerminate();
    }

    void OpenGLGraphicsAPI::Initialize()
    {
        // Initialize GLFW
        glfwInit();
    }
}