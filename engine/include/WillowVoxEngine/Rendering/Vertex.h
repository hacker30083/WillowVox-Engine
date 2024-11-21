#pragma once

#include <WillowVoxEngine/Math/Vec3.h>
#include <WillowVoxEngine/Math/Vec2.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <stddef.h>

namespace WillowVox
{
    struct Vertex
    {
        Vertex(Vec3 position, Vec2 texCoord) : position(position), texCoord(texCoord) {}

        Vec3 position;
        Vec2 texCoord;

        static void SetShaderAttributes()
        {
            OpenGLGraphicsAPI::SetShaderAttribVec3(0, sizeof(Vertex), offsetof(Vertex, position));
            OpenGLGraphicsAPI::SetShaderAttribVec2(1, sizeof(Vertex), offsetof(Vertex, texCoord));
        }
    };
}