#pragma once

#include <WillowVoxEngine/Math/Vec2.h>

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

    private:
        unsigned int programId;
    };
}