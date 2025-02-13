#pragma once

#include <WillowVox/WillowVoxDefines.h>
#include <FastNoiseLite.h>
#include <WillowVox/math/NoiseSettings.h>

namespace WillowVox
{
    class WILLOWVOX_API Noise
    {
    public:
        static FastNoiseLite noise;

        static void InitNoise();

        static float GetValue2D(NoiseSettings2D& settings, int x, int y);

        static float GetValue3D(NoiseSettings3D& settings, int x, int y, int z);

        static float GetValueLayered2D(NoiseSettings2D* settings, int layers, int x, int y);

        static float GetValueLayered3D(NoiseSettings3D* settings, int layers, int x, int y, int z);
    };
}