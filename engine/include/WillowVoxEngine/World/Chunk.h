#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Shader.h>

namespace WillowVox
{
    class Chunk
    {
    public:
        Chunk(Shader& shader);
        ~Chunk();

        void Render();

    private:
        MeshRenderer* mr;
    };
}