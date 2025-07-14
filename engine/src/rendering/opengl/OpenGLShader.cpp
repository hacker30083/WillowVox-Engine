#include <WillowVox/rendering/opengl/OpenGLShader.h>

#include <WillowVox/rendering/opengl/OpenGLAPI.h>
#include <WillowVox/core/Logger.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace WillowVox
{   

    /**
     * Initializes shader from vertex and fragment shader files
     * 
     * @param vertexShaderPath Path to vertex shader file
     * @param fragmentShaderPath Path to fragment shader file
     */
	OpenGLShader::OpenGLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            Logger::Error("Error reading shader source files: %s", e.what());
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            Logger::Error("Error compiling vertex shader! (%s): %s", vertexShaderPath, infoLog);
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            Logger::Error("Error compiling fragment shader! (%s): %s", fragmentShaderPath, infoLog);
        }

        // shader program
        _programId = glCreateProgram();
        glAttachShader(_programId, vertex);
        glAttachShader(_programId, fragment);
        glLinkProgram(_programId);
        // print linking errors if any
        glGetProgramiv(_programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_programId, 512, nullptr, infoLog);
            Logger::Error("Error linking shader program: %s", infoLog);
        }

        // delete the shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
	}


    /**
     * Creates shader from vertex and fragment shader code
     * 
     * @param vertexShaderCode Code for vertex shader (in glsl format)
     * @param fragmentShaderCode Code for fragment shader (in glsl format)
     * @param codePassed Not used
     */
    OpenGLShader::OpenGLShader(const char* vertexShaderCode, const char* fragmentShaderCode, bool codePassed)
    {
        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            Logger::Error("Error compiling vertex shader! (%s): %s", vertexShaderCode, infoLog);
        }

        // fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            Logger::Error("Error compiling fragment shader! (%s): %s", fragmentShaderCode, infoLog);
        }

        // shader program
        _programId = glCreateProgram();
        glAttachShader(_programId, vertex);
        glAttachShader(_programId, fragment);
        glLinkProgram(_programId);
        // print linking errors if any
        glGetProgramiv(_programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(_programId, 512, nullptr, infoLog);
            Logger::Error("Error linking shader program: %s", infoLog);
        }

        // delete the shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    /**
     * Delete shader program
     */
    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_programId);
    }

    /**
     * Set the shader program as active to be used for rendering until another one is chosen
     */
    void OpenGLShader::Bind()
    {
        glUseProgram(_programId);
    }

    /**
     * Set bool variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetBool(const char* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(_programId, name), (int)value);
    }

    /**
     * Set int variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetInt(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(_programId, name), value);
    }

    /**
     * Set float variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetFloat(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(_programId, name), value);
    }

    /**
     * Set vec2 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetVec2(const char* name, glm::vec2 value) const
    {
        glUniform2f(glGetUniformLocation(_programId, name), value.x, value.y);
    }

    /**
     * Set vec2 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param x First part in vec2
     * @param y Second part in vec2
     */
    void OpenGLShader::SetVec2(const char* name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(_programId, name), x, y);
    }

    /**
     * Set vec3 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetVec3(const char* name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(_programId, name), value.x, value.y, value.z);
    }

    /**
     * Set vec3 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param x First value in vec3
     * @param y Second value in vec3
     * @param z Third value in vec3
     */
    void OpenGLShader::SetVec3(const char* name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(_programId, name), x, y, z);
    }

    /**
     * Set vec4 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetVec4(const char* name, glm::vec4 value) const
    {
        glUniform4f(glGetUniformLocation(_programId, name), value.x, value.y, value.z, value.w);
    }
    
    /**
     * Set vec4 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param x First value in vec4
     * @param y Second value in vec4
     * @param z Third value in vec4
     * @param w Fourth value in vec4
     */
    void OpenGLShader::SetVec4(const char* name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(_programId, name), x, y, z, w);
    }

    /**
     * Set mat4 variable (a.k.a uniform) in shader by name
     * 
     * @param name Name of the variable (uniform) in the shader
     * @param value The value you want to set to the variable
     */
    void OpenGLShader::SetMat4(const char* name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_programId, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}