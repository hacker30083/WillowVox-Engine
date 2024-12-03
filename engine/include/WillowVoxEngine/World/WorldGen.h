#pragma once

#include <WillowVoxEngine/World/ChunkData.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <cstdint>

namespace WillowVox
{
    class WorldGen
    {
    public:
        virtual void GenerateChunkData(ChunkData& chunkData)
        {
            int i = 0;
            for (int x = 0; x < CHUNK_SIZE; x++)
            {
                for (int y = 0; y < CHUNK_SIZE; y++)
                {
                    for (int z = 0; z < CHUNK_SIZE; z++)
                    {
                        chunkData.voxels[i] = GetBlock(x + chunkData.offset.x, y + chunkData.offset.y, z + chunkData.offset.z);
                        i++;
                    }
                }
            }
        }
        
        virtual uint16_t GetBlock(int x, int y, int z)
        {
            return 1;
        }
    };
}