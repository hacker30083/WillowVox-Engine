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

        _noise = new NoiseSettings(1.05f, 10.0f);
        _worldGen = new TerrainGen(*_noise);

        _chunkManager = new ChunkManager(*_worldGen);
    }

private:
    /* Test Code */
    NoiseSettings* _noise;
    TerrainGen* _worldGen;
};