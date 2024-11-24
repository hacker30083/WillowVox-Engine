#pragma once

namespace WillowVox
{
    struct ChunkData
    {
        ChunkData(uint16_t* voxels) : voxels(voxels) {}
        ~ChunkData() { delete[] voxels; }

        uint16_t* voxels;
    };
}