#pragma once

#include <WillowVoxEngine/Math/Vec3.h>
#include <WillowVoxEngine/Math/Vec2.h>

namespace WillowVox
{
    struct Vertex
    {
        Vertex(Vec3 position, Vec2 texCoord) : position(position), texCoord(texCoord) {}

        Vec3 position;
        Vec2 texCoord;
    };
}