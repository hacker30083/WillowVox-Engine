#include <WillowVox/world/TerrainGen.h>

#include <WillowVox/core/Logger.h>
#include <WillowVox/math/Noise.h>

namespace WillowVox
{
    void TerrainGen::GenerateChunkData(ChunkData& chunkData)
    {
        // Terrain shape
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

        // Surface features
        for (int i = 0; i < m_surfaceFeatureCount; i++)
        {
            for (int x = -m_surfaceFeatures[i].sizeX - m_surfaceFeatures[i].offsetX; x < CHUNK_SIZE - m_surfaceFeatures[i].offsetX; x++)
            {
                for (int z = -m_surfaceFeatures[i].sizeZ - m_surfaceFeatures[i].offsetZ; z < CHUNK_SIZE - m_surfaceFeatures[i].offsetZ; z++)
                {
                    float noiseY = Noise::GetValueLayered2D(m_surfaceNoiseSettings, m_surfaceNoiseLayers, 
                        x + chunkData.m_offset.x, z + chunkData.m_offset.z);
                    int surfaceBlock = (int)roundf(noiseY);

                    if (surfaceBlock + m_surfaceFeatures[i].offsetY > chunkData.m_offset.y + CHUNK_SIZE || 
                        surfaceBlock + m_surfaceFeatures[i].sizeY + m_surfaceFeatures[i].offsetY < chunkData.m_offset.y)
                        continue;

                    // Check if it's in water or on sand
                    if (surfaceBlock < m_waterLevel + 2)
                        continue;
                    
                    // Check if it's in a cave
                    float caveNoise = Noise::GetValueLayered3D(m_caveNoiseSettings, m_caveNoiseLayers, x + chunkData.m_offset.x, surfaceBlock, z + chunkData.m_offset.z);
                    bool cave = caveNoise > m_caveThreshold;

                    if (cave)
                        continue;

                    float noise = Noise::GetValue2D(m_surfaceFeatures[i].noiseSettings, 
                        x + chunkData.m_offset.x, z + chunkData.m_offset.z);
                    
                    if (noise > m_surfaceFeatures[i].chance)
                    {
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
        float surfaceNoise = Noise::GetValueLayered2D(m_surfaceNoiseSettings, m_surfaceNoiseLayers, x, z);
        int surfaceBlock = (int)roundf(surfaceNoise);

        float caveNoise = Noise::GetValueLayered3D(m_caveNoiseSettings, m_caveNoiseLayers, x, y, z);
        
        // Sky
        if (y > surfaceBlock)
        {
            if (y <= m_waterLevel)
                return m_waterBlock;
            else
                return 0;
        }
        // Caves
        else if (caveNoise > m_caveThreshold)
            return 0;
        // Ground
        else
        {
            if (y == surfaceBlock)
                return m_surfaceBlock;
            else if (y < surfaceBlock - m_groundCount)
                return m_undergroundBlock;
            else
                return m_groundBlock;
        }
    }
}