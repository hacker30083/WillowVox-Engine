#pragma once

#include <cstdint>
#include <cstddef>

namespace WillowVox
{
    class OpenGLGraphicsAPI
    {
    public:
        ~OpenGLGraphicsAPI();

        void Initialize();

        static void PostGladSetup();
        static void EnableCullFace();

        static void SetShaderAttribVec2(int index, uint32_t size, std::size_t offset);
        static void SetShaderAttribVec3(int index, uint32_t size, std::size_t offset);
        static void SetShaderAttribVec3b(int index, uint32_t size, std::size_t offset);
    };
}
