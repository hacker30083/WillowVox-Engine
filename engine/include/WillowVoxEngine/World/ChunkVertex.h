#pragma once

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <glm/glm.hpp>
#include <stddef.h>

namespace WillowVox
{
    struct ChunkVertex
    {
        ChunkVertex(char xPos, char yPos, char zPos, glm::vec2 texCoord) : xPos(xPos), yPos(yPos), zPos(zPos), texCoord(texCoord) {}
        ChunkVertex(char xPos, char yPos, char zPos, float texCoordX, float texCoordY) : xPos(xPos), yPos(yPos), zPos(zPos) 
        { 
            texCoord = glm::vec2(texCoordX, texCoordY);
        }

        char xPos, yPos, zPos;
        glm::vec2 texCoord;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3b(0, sizeof(ChunkVertex), offsetof(ChunkVertex, xPos));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(ChunkVertex), offsetof(ChunkVertex, texCoord));
        }
    };
}