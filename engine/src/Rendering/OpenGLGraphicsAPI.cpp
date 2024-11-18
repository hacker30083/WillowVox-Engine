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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    }
}