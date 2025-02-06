#pragma once

#include <WillowVox/rendering/BaseMaterial.h>
#include <WillowVox/rendering/Texture.h>
#include <glm/glm.hpp>

namespace WillowVox
{
	class TextureMaterial : public BaseMaterial
	{
	public:
		TextureMaterial(Shader* shader, Texture* texture);

		void SetVertexAttributes() override;

	protected:
		void SetShaderProperties() override;

	private:
		Texture* _texture;
	};
}