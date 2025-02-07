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

        _noise = new NoiseSettings2D(10.0f, 1.05f, 3, 0.5f, 2.5f, -5);
        _worldGen = new TerrainGen(*_noise, -10);

        _chunkManager = new ChunkManager(*_worldGen);
    }

private:
    /* Test Code */
    NoiseSettings2D* _noise;
    TerrainGen* _worldGen;
};