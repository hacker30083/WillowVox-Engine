#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/World/ChunkData.h>

namespace WillowVox
{
    class Chunk
    {
    public:
        Chunk(Shader& shader);
        ~Chunk();

        void GenerateChunk();
        void Render();

    private:
        MeshRenderer* mr;
        ChunkData* chunkData;
    };
}