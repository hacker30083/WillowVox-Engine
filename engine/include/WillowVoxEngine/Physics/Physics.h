#pragma once

#include <WillowVoxEngine/World/Chunk.h>
#include <glm/glm.hpp>

#define RAY_STEP 0.01f

namespace WillowVox
{
    namespace Physics
    {
        struct RaycastResult
        {
            bool hit;
            glm::vec3 hitPos;
            Chunk* chunk;
            int blockX;
            int blockY;
            int blockZ;
            int localBlockX;
            int localBlockY;
            int localBlockZ;

            RaycastResult(bool hit, glm::vec3 hitPos, Chunk* chunk, int blockX, int blockY, int blockZ, int localBlockX, int localBlockY, int localBlockZ)
                : hit(hit), hitPos(hitPos), chunk(chunk), blockX(blockX), blockY(blockY), blockZ(blockZ), localBlockX(localBlockX), localBlockY(localBlockY), localBlockZ(localBlockZ) {}
        };

        RaycastResult Raycast(glm::vec3 startPos, glm::vec3 direction, float maxDistance);
    }
}