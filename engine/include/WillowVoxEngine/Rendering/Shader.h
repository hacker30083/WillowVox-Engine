#pragma once

#include <WillowVoxEngine/Math/Vec2.h>
#include <WillowVoxEngine/Math/Vec3.h>
#include <glm/glm.hpp>

namespace WillowVox
{
    class Shader
    {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();

        void Use();
        void SetBool(const char* name, bool value) const;
        void SetInt(const char* name, int value) const;
        void SetFloat(const char* name, float value) const;
        void SetVec2(const char* name, Vec2 value) const;
        void SetVec2(const char* name, float x, float y) const;
        void SetVec3(const char* name, Vec3 value) const;
        void SetVec3(const char* name, float x, float y, float z) const;
        void SetMat4(const char* name, glm::mat4 value) const;

    private:
        unsigned int programId;
    };
}