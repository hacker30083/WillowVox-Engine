#pragma once

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <glm/glm.hpp>
#include <stddef.h>

namespace WillowVox
{
    struct BillboardVertex
    {
        BillboardVertex(float xPos, float yPos, float zPos, glm::vec2 texCoord) : xPos(xPos), yPos(yPos), zPos(zPos), texCoord(texCoord) {}
        BillboardVertex(float xPos, float yPos, float zPos, float texCoordX, float texCoordY) : xPos(xPos), yPos(yPos), zPos(zPos) 
        { 
            texCoord = glm::vec2(texCoordX, texCoordY);
        }

        float xPos, yPos, zPos;
        glm::vec2 texCoord;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3(0, sizeof(BillboardVertex), offsetof(BillboardVertex, xPos));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(BillboardVertex), offsetof(BillboardVertex, texCoord));
        }
    };
}