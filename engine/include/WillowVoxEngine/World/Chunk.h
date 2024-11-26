#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/World/ChunkVertex.h>
#include <glm/glm.hpp>
#include <vector>

namespace WillowVox
{
    class Chunk
    {
    public:
        Chunk(Shader& shader, glm::ivec3 chunkPos, glm::vec3 worldPos);
        ~Chunk();

        void GenerateChunkMeshData();
        void GenerateChunkMesh();
        void Render();

        ChunkData* chunkData;
        ChunkData* northData;
        ChunkData* southData;
        ChunkData* eastData;
        ChunkData* westData;
        ChunkData* upData;
        ChunkData* downData;

    private:
        glm::ivec3 chunkPos;
        glm::vec3 worldPos;

        MeshRenderer* mr;
        Shader& shader;

        std::vector<ChunkVertex> vertices;
        std::vector<uint32_t> indices;
        bool ready = false;
    };
}