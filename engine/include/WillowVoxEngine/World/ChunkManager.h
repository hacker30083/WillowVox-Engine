#pragma once

#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/Math/ivec3Hash.h>
#include <WillowVoxEngine/Rendering/Camera.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>
#include <thread>
#include <mutex>

#define CHUNK_SIZE 32

namespace WillowVox
{
    class ChunkManager
    {
    public:
        ~ChunkManager();

        void Start();
        void Update();
        void Render(Camera& camera);

        int renderDistance = 10;
        int renderHeight = 3;

        // TEMP until asset manager
        Shader* terrainShader;

    private:
        void ChunkThreadUpdate();

        Chunk* chunk;

        std::unordered_map<glm::ivec3, Chunk*, ivec3Hash> chunks;
        std::unordered_map<glm::ivec3, ChunkData*, ivec3Hash> chunkData;
        std::queue<glm::ivec3> chunkQueue;
        std::queue<glm::ivec3> chunkDataQueue;
        std::queue<glm::ivec3> chunkDataDeleteQueue;
        
        std::thread chunkThread;
        std::mutex chunkMutex;

        bool shouldEnd = false;
    };
}