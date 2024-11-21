#pragma once

namespace WillowVox
{
    class OpenGLGraphicsAPI
    {
    public:
        ~OpenGLGraphicsAPI();

        void Initialize();

        static void SetShaderAttribVec2(int index, uint32_t size, uint32_t offset);
        static void SetShaderAttribVec3(int index, uint32_t size, uint32_t offset);
    };
}
