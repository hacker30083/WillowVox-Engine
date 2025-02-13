#pragma once

#include <WillowVox/WillowVoxDefines.h>

namespace WillowVox
{
    struct WILLOWVOX_API NoiseSettings2D
    {
        NoiseSettings2D(float amplitude, float frequency, int octaves, 
                        float persistence, float lacunarity, float heightOffset, float xOffset = 0, float yOffset = 0)
            : m_amplitude(amplitude), m_frequency(frequency), m_octaves(octaves), 
              m_persistence(persistence), m_lacunarity(lacunarity), m_heightOffset(heightOffset),
              m_xOffset(xOffset), m_yOffset(yOffset) {}

        float m_amplitude;
        float m_frequency;
        int m_octaves;
        float m_persistence;
        float m_lacunarity;
        float m_heightOffset;
        float m_xOffset, m_yOffset;
    };
    
    struct WILLOWVOX_API NoiseSettings3D
    {
        NoiseSettings3D(float amplitude, float frequency, int octaves, 
                        float persistence, float lacunarity, float xOffset = 0, float yOffset = 0, float zOffset = 0)
            : m_amplitude(amplitude), m_frequency(frequency), m_octaves(octaves), 
              m_persistence(persistence), m_lacunarity(lacunarity),
              m_xOffset(xOffset), m_yOffset(yOffset), m_zOffset(zOffset) {}

        float m_amplitude;
        float m_frequency;
        int m_octaves;
        float m_persistence;
        float m_lacunarity;
        float m_xOffset, m_yOffset, m_zOffset;
    };
}