#pragma once

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <glm/glm.hpp>
#include <stddef.h>

namespace WillowVox
{
    struct FluidVertex
    {
        FluidVertex(char xPos, char yPos, char zPos, glm::vec2 texCoord, char top) : xPos(xPos), yPos(yPos), zPos(zPos), texCoord(texCoord), top(top) {}
        FluidVertex(char xPos, char yPos, char zPos, float texCoordX, float texCoordY, char top) : xPos(xPos), yPos(yPos), zPos(zPos), top(top) 
        { 
            texCoord = glm::vec2(texCoordX, texCoordY);
        }

        char xPos, yPos, zPos;
        glm::vec2 texCoord;
        char top;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3b(0, sizeof(FluidVertex), offsetof(FluidVertex, xPos));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(FluidVertex), offsetof(FluidVertex, texCoord));
            OpenGLGraphicsAPI::SetShaderAttribByte(2, sizeof(FluidVertex), offsetof(FluidVertex, top));
        }
    };
}