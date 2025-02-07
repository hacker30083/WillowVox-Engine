#pragma once

#include <FastNoiseLite.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    class Noise
    {
    public:
        static FastNoiseLite noise;

        static void InitNoise();

        static float GetValue2D(NoiseSettings2D& settings, int x, int y);

        static float GetValue3D(NoiseSettings3D& settings, int x, int y, int z);
    };
}