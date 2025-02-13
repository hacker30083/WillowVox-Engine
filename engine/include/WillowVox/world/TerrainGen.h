#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <WillowVox/world/WorldGen.h>
#include <WillowVox/math/NoiseSettings.h>
#include <WillowVox/world/SurfaceFeature.h>
#include <cstdint>

namespace WillowVox
{
    class WILLOWVOX_API TerrainGen : public WorldGen
    {
    public:
        TerrainGen(NoiseSettings2D* surfaceNoiseSettings, int surfaceNoiseLayers, NoiseSettings3D* caveNoiseSettings, 
            int caveNoiseLayers, float caveThreshold, int waterLevel, int groundCount, 
            uint16_t undergroundBlock, uint16_t groundBlock, uint16_t surfaceBlock, uint16_t waterBlock, 
            SurfaceFeature* surfaceFeatures, int surfaceFeatureCount)
            
            : m_surfaceNoiseSettings(surfaceNoiseSettings), m_surfaceNoiseLayers(surfaceNoiseLayers),
            m_caveNoiseSettings(caveNoiseSettings), m_caveNoiseLayers(caveNoiseLayers), m_caveThreshold(caveThreshold), 
            m_waterLevel(waterLevel), m_groundCount(groundCount), m_undergroundBlock(undergroundBlock), 
            m_groundBlock(groundBlock), m_surfaceBlock(surfaceBlock), m_waterBlock(waterBlock),
            m_surfaceFeatures(surfaceFeatures), m_surfaceFeatureCount(surfaceFeatureCount) {}

        void GenerateChunkData(ChunkData& chunkData) override;

        uint16_t GetBlock(int x, int y, int z) override;

        NoiseSettings2D* m_surfaceNoiseSettings;
        NoiseSettings3D* m_caveNoiseSettings;
        int m_surfaceNoiseLayers, m_caveNoiseLayers;
        float m_caveThreshold;
        int m_waterLevel, m_groundCount;
        uint16_t m_undergroundBlock, m_groundBlock, m_surfaceBlock, m_waterBlock;
        SurfaceFeature* m_surfaceFeatures;
        int m_surfaceFeatureCount;
    };
}