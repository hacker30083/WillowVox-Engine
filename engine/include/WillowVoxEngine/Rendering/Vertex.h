#pragma once

#include <WillowVoxEngine/Math/Vec3.h>

namespace WillowVox
{
    struct Vertex
    {
        Vertex(Vec3 position) : position(position) {}

        Vec3 position;
    };
}