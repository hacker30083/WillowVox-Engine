#include <WillowVox/rendering/engine-default/TextureMaterial.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/engine-default/Vertex.h>

namespace WillowVox
{
	TextureMaterial::TextureMaterial(Shader* shader, Texture* texture)
		: BaseMaterial(shader)
	{
		_texture = texture;
	}

	void TextureMaterial::SetVertexAttributes()
	{
		RenderingAPI::m_renderingAPI->SetVertexAttrib3f(0, sizeof(Vertex), offsetof(Vertex, m_position));
		RenderingAPI::m_renderingAPI->SetVertexAttrib2f(1, sizeof(Vertex), offsetof(Vertex, m_texPos));
	}

	void TextureMaterial::SetShaderProperties()
	{
		_texture->BindTexture(Texture::TEX00);
		RenderingAPI::m_renderingAPI->SetBlending(false);
	}
}