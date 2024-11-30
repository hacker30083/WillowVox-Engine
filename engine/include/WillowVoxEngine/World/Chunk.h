#pragma once

#include <WillowVoxEngine/Rendering/MeshRenderer.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/World/ChunkVertex.h>
#include <WillowVoxEngine/World/FluidVertex.h>
#include <WillowVoxEngine/World/BillboardVertex.h>
#include <glm/glm.hpp>
#include <vector>

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
        bool ready = false;
    };
}