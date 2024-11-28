#include <WillowVoxEngine/Math/Noise.h>

namespace WillowVox
{
    FastNoiseLite Noise::noise;

    void Noise::InitNoise()
    {
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    }

    float Noise::GetValue2D(int x, int y)
    {
        return noise.GetNoise((float)x * 10.4f, (float)y * 10.4f);
    }

    float Noise::GetValue3D(int x, int y, int z)
    {
        return noise.GetNoise((float)x * 10.4f, (float)y * 10.4f, float(z) * 10.4f);
    }
}