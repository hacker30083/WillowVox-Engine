#pragma once

#include <WillowVoxEngine/World/WorldGen.h>

namespace WillowVox
{
    class TerrainGen : public WorldGen
    {
    public:
        uint16_t GetBlock(int x, int y, int z) override;
    };
}