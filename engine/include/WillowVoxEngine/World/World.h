#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/Camera.h>
#include <vector>

namespace WillowVox
{
    class World
    {
    public:
        void Start();
        void Update();
        void Render(Camera& camera);

    private:
        std::vector<MeshRenderer*> meshRenderers;
        // vvv Test code vvv
        Chunk* chunk;
        Shader* chunkShader;
    };
}