#pragma once

#include <WillowVox/WillowVox.h>
#include <WillowVox/math/NoiseSettings.h>
#include <WillowVox/world/TerrainGen.h>

using namespace WillowVox;

class TestWorld : public World
{
public:
    TestWorld(Camera* player)
    {
        m_mainCamera = player;

        _surfaceNoise = new NoiseSettings2D[] {
            { 20.0f, 0.5f, 1, 0, 0, -5 },
            { 3.0f, 2.4f, 1, 0, 0, 0 },
        };

        _caveNoise = new CaveNoiseSettings[] {
            { 2.5f, 1, 0, 0, 0.5f }
        };

        _oreNoise = new OreNoiseSettings[]{
            { 4.5f, 1, 0, 0, 0.7f, 2, 14.0f, 34.0f, 23.0f }
        };

        _surfaceFeatures = new SurfaceFeature[] {
            // Tree
            {
                { 1.0f, 40.23f, 1, 0, 0, 0 },
                { 
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 1, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,

                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 4, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,

                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 4, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0,

                    0, 5, 5, 5, 0,
                    5, 5, 5, 5, 5,
                    5, 5, 4, 5, 5,
                    5, 5, 5, 5, 5,
                    0, 5, 5, 5, 0,

                    0, 5, 5, 5, 0,
                    5, 5, 5, 5, 5,
                    5, 5, 4, 5, 5,
                    5, 5, 5, 5, 5,
                    0, 5, 5, 5, 0,

                    0, 0, 0, 0, 0,
                    0, 0, 5, 0, 0,
                    0, 5, 5, 5, 0,
                    0, 0, 5, 0, 0,
                    0, 0, 0, 0, 0,

                    0, 0, 0, 0, 0,
                    0, 0, 5, 0, 0,
                    0, 5, 5, 5, 0,
                    0, 0, 5, 0, 0,
                    0, 0, 0, 0, 0,

                },
                { 
                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, true,  false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, true,  false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, true,  false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, true,  false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, true,  false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,

                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,
                    false, false, false, false, false,
                },
                5,
                7,
                5,
                -2,
                0,
                -2,
                0.9f
                },
            // Tall Grass
            {
                { 1.0f, 43.54f, 1, 0, 0, 0 },
                {
                    2, 7, 8
                },
                {
                    false, false, false
                },
                1,
                3,
                1,
                0,
                0,
                0,
                0.7f
            },
            // Grass
            {
                { 1.0f, 50.03f, 1, 0, 0, 0 },
                {
                    2, 6
                },
                {
                    false, false
                },
                1,
                2,
                1,
                0,
                0,
                0,
                0.6f
            },
            // Poppy
            {
                { 1.0f, 30.5f, 1, 0, 0, 0 },
                {
                    2, 9
                },
                {
                    false, false
                },
                1,
                2,
                1,
                0,
                0,
                0,
                0.8f
            },
            // White Tulip
            {
                { 1.0f, 36.43f, 1, 0, 0, 0 },
                {
                    2, 10
                },
                {
                    false, false
                },
                1,
                2,
                1,
                0,
                0,
                0,
                0.8f
            },
            // Pink Tulip
            {
                { 1.0f, 32.23f, 1, 0, 0, 0 },
                {
                    2, 11
                },
                {
                    false, false
                },
                1,
                2,
                1,
                0,
                0,
                0,
                0.8f
            },
            // Orange Tulip
            {
                { 1.0f, 38.34f, 1, 0, 0, 0 },
                {
                    2, 12
                },
                {
                    false, false
                },
                1,
                2,
                1,
                0,
                0,
                0,
                0.8f
            },        
        };

        _worldGen = new TerrainGen(0, _surfaceNoise, 2, _caveNoise, 1, _oreNoise, 1,
            _surfaceFeatures, 7);

        m_chunkManager = new ChunkManager(*_worldGen);
    }

private:
    /* Test Code */
    NoiseSettings2D* _surfaceNoise;
    CaveNoiseSettings* _caveNoise;
    OreNoiseSettings* _oreNoise;
    SurfaceFeature* _surfaceFeatures;
    TerrainGen* _worldGen;
};