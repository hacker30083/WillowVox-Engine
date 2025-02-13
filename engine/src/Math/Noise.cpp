#include <WillowVox/math/Noise.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    FastNoiseLite Noise::noise;

    void Noise::InitNoise()
    {
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    }

    float Noise::GetValue2D(NoiseSettings2D& settings, int x, int y)
    {
        // Get a 2D noise value starting at heightOffset and using octaves
        float value = settings.m_heightOffset;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((float)x * freq, (float)y * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;   
    }

    float Noise::GetValue3D(NoiseSettings3D& settings, int x, int y, int z)
    { 
        // Get a 3D noise value using octaves
        float value = 0;
        float freq = settings.m_frequency;
        float amp = settings.m_amplitude;
        for (int i = 0; i < settings.m_octaves; i++)
        {
            value += noise.GetNoise((float)x * freq, (float)y * freq, (float)z * freq) * amp;
            freq *= settings.m_lacunarity;
            amp *= settings.m_persistence;
        }
        return value;
    }

    float Noise::GetValueLayered2D(NoiseSettings2D* settings, int layers, int x, int y)
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
                value += noise.GetNoise((float)x * freq, (float)y * freq) * amp;
                freq *= settings[l].m_lacunarity;
                amp *= settings[l].m_persistence;
            }

            totalValue += value;
        }

        return totalValue;
    }

    float Noise::GetValueLayered3D(NoiseSettings3D* settings, int layers, int x, int y, int z)
    {
        // Get a 3D noise value
        float totalValue = 0;

        for (int l = 0; l < layers; l++)
        {
            float value = 0;
            float freq = settings[l].m_frequency;
            float amp = settings[l].m_amplitude;
            for (int i = 0; i < settings[l].m_octaves; i++)
            {
                value += noise.GetNoise((float)x * freq, (float)y * freq, (float)z * freq) * amp;
                freq *= settings[l].m_lacunarity;
                amp *= settings[l].m_persistence;
            }

            totalValue += value;
        }

        return totalValue;
    }
}