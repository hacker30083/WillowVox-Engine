#include <WillowVox/rendering/engine-default/ChunkSolidMaterial.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/engine-default/ChunkVertex.h>
#include <WillowVox/core/Logger.h>

namespace WillowVox
{
	ChunkSolidMaterial::ChunkSolidMaterial(Shader* shader, Texture* texture)
		: BaseMaterial(shader)
	{
		_texture = texture;
	}

	void ChunkSolidMaterial::SetVertexAttributes()
	{
		RenderingAPI::m_renderingAPI->SetVertexAttrib3b(0, sizeof(ChunkVertex), offsetof(ChunkVertex, m_x));
		RenderingAPI::m_renderingAPI->SetVertexAttrib2f(1, sizeof(ChunkVertex), offsetof(ChunkVertex, m_texPos));
		RenderingAPI::m_renderingAPI->SetVertexAttrib1b(2, sizeof(ChunkVertex), offsetof(ChunkVertex, m_direction));
	}

	void ChunkSolidMaterial::SetShaderProperties()
	{
		_texture->BindTexture(Texture::TEX00);
		RenderingAPI::m_renderingAPI->SetBlending(false);
	}
}