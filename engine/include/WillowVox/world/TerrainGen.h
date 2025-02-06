#pragma once

#include <WillowVox/world/WorldGen.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    class TerrainGen : public WorldGen
    {
    public:
        TerrainGen(NoiseSettings2D& noiseSettings, int waterLevel)
            : m_noiseSettings(noiseSettings), m_waterLevel(waterLevel) {}

        uint16_t GetBlock(int x, int y, int z) override;

        NoiseSettings2D& m_noiseSettings;
        int m_waterLevel;
    };
}