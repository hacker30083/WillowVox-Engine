#include <WillowVox/rendering/BaseMaterial.h>

namespace WillowVox
{
	BaseMaterial::BaseMaterial(Shader* shader)
	{
		_shader = shader;
	}

	void BaseMaterial::Bind()
	{
		_shader->Bind();
		SetShaderProperties();
	}

	void BaseMaterial::SetCameraShaderProperties(const glm::mat4& view, const glm::mat4& projection)
	{
		_shader->SetMat4("view", view);
		_shader->SetMat4("projection", projection);
	}

	void BaseMaterial::SetModelShaderProperties(const glm::vec3& model)
	{
		_shader->SetVec3("model", model);
	}
}