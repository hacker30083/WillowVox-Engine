#include <WillowVox/rendering/engine-default/RawTriMaterial.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/rendering/engine-default/Vertex.h>

namespace WillowVox
{
	RawTriMaterial::RawTriMaterial(Shader* shader, glm::vec4 color)
		: BaseMaterial(shader)
	{
		_color = color;
	}

	void RawTriMaterial::SetVertexAttributes()
	{
		RenderingAPI::m_renderingAPI->SetVertexAttrib3f(0, sizeof(Vertex), offsetof(Vertex, m_position));
	}

	void RawTriMaterial::SetShaderProperties()
	{
		_shader->SetVec4("color", _color);
		RenderingAPI::m_renderingAPI->SetBlending(false);
	}
}