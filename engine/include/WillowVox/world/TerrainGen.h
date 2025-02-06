#pragma once

#include <WillowVox/world/WorldGen.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    class TerrainGen : public WorldGen
    {
    public:
        TerrainGen(NoiseSettings& noiseSettings)
            : noiseSettings(noiseSettings) {}

        uint16_t GetBlock(int x, int y, int z) override;

        NoiseSettings& noiseSettings;
    };
}