#pragma once

#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <stddef.h>

namespace WillowVox
{
    struct Vertex
    {
        Vertex(glm::vec3 position, glm::vec2 texCoord) : position(position), texCoord(texCoord) {}

        glm::vec3 position;
        glm::vec2 texCoord;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3(0, sizeof(Vertex), offsetof(Vertex, position));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(Vertex), offsetof(Vertex, texCoord));
        }
    };
}