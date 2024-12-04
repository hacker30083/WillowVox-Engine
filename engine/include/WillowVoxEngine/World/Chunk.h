#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/World/ChunkVertex.h>
#include <WillowVoxEngine/World/FluidVertex.h>
#include <WillowVoxEngine/World/BillboardVertex.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

namespace WillowVox
{
    class Chunk
    {
    public:
        Chunk(Shader& solidShader, Shader& fluidShader, Shader& billboardShader, glm::ivec3 chunkPos, glm::vec3 worldPos);
        ~Chunk();

        void GenerateChunkMeshData();
        void GenerateChunkMesh();
        void RenderSolid();
        void RenderTransparent();

        uint16_t GetBlockIdAtPos(int x, int y, int z);
        void SetBlock(int x, int y, int z, uint16_t block);

        ChunkData* chunkData;
        ChunkData* northData;
        ChunkData* southData;
        ChunkData* eastData;
        ChunkData* westData;
        ChunkData* upData;
        ChunkData* downData;

        glm::ivec3 chunkPos;
        bool ready = false;

    private:
        glm::vec3 worldPos;

        MeshRenderer* solidMeshRenderer;
        MeshRenderer* fluidMeshRenderer;
        MeshRenderer* billboardMeshRenderer;
        Shader& solidShader;
        Shader& fluidShader;
        Shader& billboardShader;

        std::vector<ChunkVertex> solidVertices;
        std::vector<uint32_t> solidIndices;
        std::vector<FluidVertex> fluidVertices;
        std::vector<uint32_t> fluidIndices;
        std::vector<BillboardVertex> billboardVertices;
        std::vector<uint32_t> billboardIndices;
    };
}