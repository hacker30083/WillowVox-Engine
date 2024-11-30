#include <WillowVoxEngine/World/TerrainGen.h>

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Math/Noise.h>

namespace WillowVox
{
    uint16_t TerrainGen::GetBlock(int x, int y, int z)
    {
        float noise = Noise::GetValue2D(x, z) + 10;
        uint16_t block = (uint16_t)roundf(noise);

        if (y <= block)
            return 1;
        else if (y == block + 1)
            return 2;
        else
            return 0;
    }
}