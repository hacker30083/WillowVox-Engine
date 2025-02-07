#pragma once

namespace WillowVox
{
    struct NoiseSettings2D
    {
        NoiseSettings2D(float amplitude, float frequency, int octaves, 
                        float persistence, float lacunarity, float heightOffset)
            : m_amplitude(amplitude), m_frequency(frequency), m_octaves(octaves), 
              m_persistence(persistence), m_lacunarity(lacunarity), m_heightOffset(heightOffset) {}

        float m_amplitude;
        float m_frequency;
        int m_octaves;
        float m_persistence;
        float m_lacunarity;
        float m_heightOffset;
    };
    
    struct NoiseSettings3D
    {
        NoiseSettings3D(float amplitude, float frequency, int octaves, 
                        float persistence, float lacunarity, float noiseThreshold)
            : m_amplitude(amplitude), m_frequency(frequency), m_octaves(octaves), 
              m_persistence(persistence), m_lacunarity(lacunarity), m_noiseThreshold(noiseThreshold) {}

        float m_amplitude;
        float m_frequency;
        int m_octaves;
        float m_persistence;
        float m_lacunarity;
        float m_noiseThreshold;
    };
}