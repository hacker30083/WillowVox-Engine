#pragma once

#include <FastNoiseLite.h>

namespace WillowVox
{
    class Noise
    {
    public:
        static FastNoiseLite noise;

        static void InitNoise();

        static float GetValue2D(int x, int y);

        static float GetValue3D(int x, int y, int z);
    };
}