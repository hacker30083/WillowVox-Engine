#pragma once

#include <WillowVoxEngine/World/Chunk.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <WillowVoxEngine/Math/ivec3Hash.h>

namespace WillowVox
{
    class ChunkManager
    {
    public:
    private:
        std::unordered_map<glm::ivec3, Chunk*, ivec3Hash> chunks;
    };
}