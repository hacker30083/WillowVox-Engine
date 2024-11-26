#pragma once

#include <WillowVoxEngine/World/WorldGlobals.h>
#include <cstdint>

namespace WillowVox
{
    struct ChunkData
    {
    public:
        ChunkData(uint16_t* voxels) : voxels(voxels) {}
        ChunkData() { voxels = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]; }
        ~ChunkData() { delete[] voxels; }

        inline int GetIndex(int x, int y, int z) const
        {
            return x * CHUNK_SIZE * CHUNK_SIZE + z * CHUNK_SIZE + y;
        }

        uint16_t GetBlock(int x, int y, int z)
        {
            return voxels[GetIndex(x, y, z)];
        }

        uint16_t* voxels;
    };
}