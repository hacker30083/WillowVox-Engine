#pragma once

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <glm/glm.hpp>
#include <stddef.h>

namespace WillowVox
{
    struct FluidVertex
    {
        FluidVertex(char xPos, char yPos, char zPos, glm::vec2 texCoord, char direction, char top) : xPos(xPos), yPos(yPos), zPos(zPos), texCoord(texCoord), direction(direction), top(top) {}
        FluidVertex(char xPos, char yPos, char zPos, float texCoordX, float texCoordY, char direction, char top) : xPos(xPos), yPos(yPos), zPos(zPos), direction(direction), top(top) 
        { 
            texCoord = glm::vec2(texCoordX, texCoordY);
        }

        char xPos, yPos, zPos;
        glm::vec2 texCoord;
        char direction;
        char top;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3b(0, sizeof(FluidVertex), offsetof(FluidVertex, xPos));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(FluidVertex), offsetof(FluidVertex, texCoord));
            OpenGLGraphicsAPI::SetShaderAttribByte(2, sizeof(FluidVertex), offsetof(FluidVertex, direction));
            OpenGLGraphicsAPI::SetShaderAttribByte(3, sizeof(FluidVertex), offsetof(FluidVertex, top));
        }
    };
}