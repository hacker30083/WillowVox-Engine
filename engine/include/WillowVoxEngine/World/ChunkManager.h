#pragma once

#include <WillowVoxEngine/World/Chunk.h>
#include <glm/glm.hpp>
#include <unordered_map>

namespace WillowVox
{
    class ChunkManager
    {
    public:
    private:
        std::unordered_map<glm::ivec3, Chunk*> chunks;
    };
}