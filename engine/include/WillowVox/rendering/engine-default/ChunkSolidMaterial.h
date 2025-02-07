#pragma once

#include <WillowVox/rendering/BaseMaterial.h>
#include <WillowVox/rendering/Texture.h>
#include <glm/glm.hpp>

namespace WillowVox
{
	class ChunkSolidMaterial : public BaseMaterial
	{
	public:
		ChunkSolidMaterial(Shader* shader, Texture* texture);

		void SetVertexAttributes() override;

	protected:
		void SetShaderProperties() override;

	private:
		Texture* _texture;
	};
}