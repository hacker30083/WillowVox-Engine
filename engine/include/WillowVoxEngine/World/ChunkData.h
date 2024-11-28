#pragma once

#include <WillowVoxEngine/World/WorldGlobals.h>
#include <glm/glm.hpp>
#include <cstdint>

namespace WillowVox
{
    struct ChunkData
    {
    public:
        ChunkData(uint16_t* voxels, glm::ivec3 offset) : voxels(voxels), offset(offset) {}
        ChunkData() { voxels = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]; }
        ~ChunkData() { delete[] voxels; }

        inline int GetIndex(int x, int y, int z) const
        {
            return x * CHUNK_SIZE * CHUNK_SIZE + y * CHUNK_SIZE + z;
        }

        uint16_t GetBlock(int x, int y, int z)
        {
            return voxels[GetIndex(x, y, z)];
        }

        uint16_t* voxels;
        glm::ivec3 offset;
    };
}