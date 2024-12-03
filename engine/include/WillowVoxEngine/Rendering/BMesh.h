#pragma once

#include <WillowVoxEngine/Rendering/Shader.h>

namespace WillowVox
{
    class BMesh
    {
    public:
        virtual ~BMesh() = default;

        virtual void Render(Shader& shader) = 0;
    };
}