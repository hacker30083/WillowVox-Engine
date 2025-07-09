#include <WillowVox/math/Noise.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    FastNoiseLite Noise::noise;

    void Noise::InitNoise()
    {
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    }

    float Noise::GetValue2D(NoiseSettings2D& settings, int seed, float x, float y)
    {
        // Get a 2D noise value starting at heightOffset and using octaves
        float value = settings.m_heightOffset;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((x + seed + settings.m_xOffset) * freq, (y + seed + settings.m_yOffset) * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;   
    }

    float Noise::GetValueLayered2D(NoiseSettings2D* settings, int layers, int seed, float x, float y)
    {
        // Get a 2D noise value starting at heightOffset and using octaves
        float totalValue = 0;

        for (int l = 0; l < layers; l++)
        {
            float value = settings[l].m_heightOffset;
            float freq = settings[l].m_frequency;
            float amp = settings[l].m_amplitude;
            for (int i = 0; i < settings[l].m_octaves; i++)
            {
                value += noise.GetNoise((x + seed + settings[l].m_xOffset) * freq, (y + seed + settings[l].m_yOffset) * freq) * amp;
                freq *= settings[l].m_lacunarity;
                amp *= settings[l].m_persistence;
            }

            totalValue += value;
        }

        return totalValue;
    }

    float Noise::GetValue3D(NoiseSettings3D& settings, int seed, float x, float y, float z)
    { 
        // Get a 3D noise value using octaves
        float value = 0;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((x + seed + settings.m_xOffset) * freq, (y + seed + settings.m_yOffset) * freq, (z + seed + settings.m_zOffset) * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;
    }

    float Noise::GetValue3D(CaveNoiseSettings& settings, int seed, float x, float y, float z)
    {
        // Get a 3D noise value using octaves
        float value = 0;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((x + seed + settings.m_xOffset) * freq, (y + seed + settings.m_yOffset) * freq, (z + seed + settings.m_zOffset) * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;
    }

    float Noise::GetValue3D(OreNoiseSettings& settings, int seed, float x, float y, float z)
    {
        // Get a 3D noise value using octaves
        float value = 0;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((x + seed + settings.m_xOffset) * freq, (y + seed + settings.m_yOffset) * freq, (z + seed + settings.m_zOffset) * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;
    }
}