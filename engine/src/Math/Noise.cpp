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
        // Get a 2D noise value using octaves
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
}