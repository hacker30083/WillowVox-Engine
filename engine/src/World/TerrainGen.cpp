#include <WillowVoxEngine/World/TerrainGen.h>

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Math/Noise.h>

namespace WillowVox
{
    uint16_t TerrainGen::GetBlock(int x, int y, int z)
    {
        float noise = Noise::GetValue2D(x, z) + 10;
        uint16_t block = (uint16_t)roundf(noise);
        return y < block ? 1 : 0;
    }
}