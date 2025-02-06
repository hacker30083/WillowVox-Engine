#include <WillowVox/rendering/engine-default/ChunkFluidMaterial.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/engine-default/FluidVertex.h>

namespace WillowVox
{
	ChunkFluidMaterial::ChunkFluidMaterial(Shader* shader, Texture* texture)
		: BaseMaterial(shader)
	{
		_texture = texture;
	}

	void ChunkFluidMaterial::SetVertexAttributes()
	{
		RenderingAPI::m_renderingAPI->SetVertexAttrib3b(0, sizeof(FluidVertex), offsetof(FluidVertex, m_x));
		RenderingAPI::m_renderingAPI->SetVertexAttrib2f(1, sizeof(FluidVertex), offsetof(FluidVertex, m_texPos));
		RenderingAPI::m_renderingAPI->SetVertexAttrib1b(2, sizeof(FluidVertex), offsetof(FluidVertex, m_direction));
		RenderingAPI::m_renderingAPI->SetVertexAttrib1b(3, sizeof(FluidVertex), offsetof(FluidVertex, m_top));
	}

	void ChunkFluidMaterial::SetShaderProperties()
	{
		_texture->BindTexture(Texture::TEX00);
		RenderingAPI::m_renderingAPI->SetBlending(true);
	}
}