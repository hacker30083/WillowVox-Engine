#include <WillowVox/world/TerrainGen.h>

#include <WillowVox/core/Logger.h>
#include <WillowVox/math/Noise.h>

namespace WillowVox
{
    void TerrainGen::GenerateChunkData(ChunkData& chunkData)
    {
        // Terrain shape
        GenerateChunkBlocks(chunkData);
        GenerateSurfaceFeatures(chunkData);
    }

    inline void TerrainGen::GenerateChunkBlocks(ChunkData& chunkData)
    {
        int i = 0;
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    chunkData.m_voxels[i] = GetBlock(x + chunkData.m_offset.x, y + chunkData.m_offset.y, z + chunkData.m_offset.z);
                    i++;
                }
            }
        }
    }

    inline void TerrainGen::GenerateSurfaceFeatures(ChunkData& chunkData)
    {        
        // Surface features
        for (int i = 0; i < m_surfaceFeatureCount; i++)
        {
            for (int x = -m_surfaceFeatures[i].sizeX - m_surfaceFeatures[i].offsetX; x < CHUNK_SIZE - m_surfaceFeatures[i].offsetX; x++)
            {
                for (int z = -m_surfaceFeatures[i].sizeZ - m_surfaceFeatures[i].offsetZ; z < CHUNK_SIZE - m_surfaceFeatures[i].offsetZ; z++)
                {
                    int surfaceBlock = GetSurfaceBlock(x + chunkData.m_offset.x, z + chunkData.m_offset.z);

                    if (surfaceBlock + m_surfaceFeatures[i].offsetY > chunkData.m_offset.y + CHUNK_SIZE || 
                        surfaceBlock + m_surfaceFeatures[i].sizeY + m_surfaceFeatures[i].offsetY < chunkData.m_offset.y)
                        continue;
                    
                    if (!IsValidSurfaceFeaturePlacement(x + chunkData.m_offset.x, surfaceBlock, z + chunkData.m_offset.z, surfaceBlock))
                        continue;

                    // Noise check
                    float noise = Noise::GetValue2D(m_surfaceFeatures[i].noiseSettings, m_seed, 
                        x + chunkData.m_offset.x, z + chunkData.m_offset.z);
                    
                    if (noise > m_surfaceFeatures[i].chance)
                    {
                        // Place feature
                        int featureX = x + chunkData.m_offset.x;
                        int featureY = surfaceBlock;
                        int featureZ = z + chunkData.m_offset.z;

                        for (int fX = 0; fX < m_surfaceFeatures[i].sizeX; fX++)
                        {
                            for (int fY = 0; fY < m_surfaceFeatures[i].sizeY; fY++)
                            {
                                for (int fZ = 0; fZ < m_surfaceFeatures[i].sizeZ; fZ++)
                                {
                                    int localX = featureX + fX + m_surfaceFeatures[i].offsetX - chunkData.m_offset.x;
                                    //std::cout << "FeatureX: " << featureX << ", fX: " << fX << ", startX: " << startX << ", localX: " << localX << '\n';
                                    int localY = featureY + fY + m_surfaceFeatures[i].offsetY - chunkData.m_offset.y;
                                    //std::cout << "FeatureY: " << featureY << ", fY: " << fY << ", startY: " << startY << ", localY: " << localY << '\n';
                                    int localZ = featureZ + fZ + m_surfaceFeatures[i].offsetZ - chunkData.m_offset.z;
                                    //std::cout << "FeatureZ: " << featureZ << ", fZ: " << fZ << ", startZ: " << startZ << ", localZ: " << localZ << '\n';

                                    if (localX >= CHUNK_SIZE || localX < 0)
                                        continue;
                                    if (localY >= CHUNK_SIZE || localY < 0)
                                        continue;
                                    if (localZ >= CHUNK_SIZE || localZ < 0)
                                        continue;
                                    
                                    int featureIndex = fY * m_surfaceFeatures[i].sizeX * m_surfaceFeatures[i].sizeZ + 
                                        fX * m_surfaceFeatures[i].sizeZ  + 
                                        fZ;
                                    //std::cout << "Feature Index: " << featureIndex << '\n';
                                    
                                    if (m_surfaceFeatures[i].replaceBlock[featureIndex] || 
                                        chunkData.GetBlock(localX, localY, localZ) == 0)
                                        chunkData.SetBlock(localX, localY, localZ, 
                                            m_surfaceFeatures[i].blocks[featureIndex]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    uint16_t TerrainGen::GetBlock(int x, int y, int z)
    {
        int surfaceBlock = GetSurfaceBlock(x, z);
        
        // Sky
        if (y > surfaceBlock)
            return GetSkyBlock(x, y, z, surfaceBlock);
        // Caves
        else if (IsCave(x, y, z, surfaceBlock))
            return GetCaveBlock(x, y, z, surfaceBlock);
        else
        {
            uint16_t ore = IsOre(x, y, z, surfaceBlock);
            // Ore
            if (ore != 0)
                return GetOreBlock(x, y, z, surfaceBlock, ore);
            // Ground
            else
                return GetGroundBlock(x, y, z, surfaceBlock);
        }
    }

    inline uint16_t TerrainGen::GetSkyBlock(int x, int y, int z, int surfaceBlock)
    {
        return 0;
    }

    inline uint16_t TerrainGen::GetGroundBlock(int x, int y, int z, int surfaceBlock)
    {
        return 1;
    }

    inline uint16_t TerrainGen::GetCaveBlock(int x, int y, int z, int surfaceBlock)
    {
        return 0;
    }

    inline uint16_t TerrainGen::GetOreBlock(int x, int y, int z, int surfaceBlock, uint16_t block)
    {
        return block;
    }

    inline bool TerrainGen::IsCave(int x, int y, int z, int surfaceBlock)
    {
        for (int l = 0; l < m_caveNoiseLayers; l++)
        {
            float noise = Noise::GetValue3D(m_caveNoiseSettings[l], m_seed, x, y, z);
            if (noise > m_caveNoiseSettings[l].m_noiseThreshold)
                return true;
        }

        return false;
    }

    inline uint16_t TerrainGen::IsOre(int x, int y, int z, int surfaceBlock)
    {
        for (int l = 0; l < m_oreNoiseLayers; l++)
        {
            float noise = Noise::GetValue3D(m_oreNoiseSettings[l], m_seed, x, y, z);
            if (noise > m_oreNoiseSettings[l].m_noiseThreshold)
                return m_oreNoiseSettings[l].m_replaceBlock;
        }

        return 0;
    }

    inline int TerrainGen::GetSurfaceBlock(int x, int z)
    {
        float surfaceNoise = Noise::GetValueLayered2D(m_surfaceNoiseSettings, m_surfaceNoiseLayers, m_seed, x, z);
        return (int)roundf(surfaceNoise);
    }

    inline bool TerrainGen::IsValidSurfaceFeaturePlacement(int x, int y, int z, int surfaceBlock)
    {
        // Check if it's a cave
        if (IsCave(x, y, z, surfaceBlock))
            return false;

        return true;
    }
}