#pragma once

#include <WillowVox/rendering/Texture.h>

namespace WillowVox
{
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(const char* path);
        ~OpenGLTexture();

        void BindTexture(TexSlot slot) override;

    private:
        unsigned int _textureId;
    };
}