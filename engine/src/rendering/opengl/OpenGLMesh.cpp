#include <WillowVox/rendering/opengl/OpenGLMesh.h>

#include <WillowVox/rendering/opengl/OpenGLAPI.h>

namespace WillowVox
{
	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glGenBuffers(1, &_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
	}

	void OpenGLMesh::Render(const glm::vec3& position, BaseMaterial& material, const PolygonMode& mode) // Bind material and render
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		//Logger::EngineLog("%d (%f %f %f): %d", _vao, position.x, position.y, position.z, _numTriangles);

		material.Bind();
		material.SetModelShaderProperties(position);

		switch (mode)
		{
		case PolygonMode::Triangle:
			glDrawElements(GL_TRIANGLES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		case PolygonMode::Line:
			glDrawElements(GL_LINES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		}
	}

	void OpenGLMesh::Render(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& position, BaseMaterial& material, const PolygonMode& mode)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		material.Bind();
		material.SetCameraShaderProperties(view, projection);
		material.SetModelShaderProperties(position);

		switch (mode)
		{
		case PolygonMode::Triangle:
			glDrawElements(GL_TRIANGLES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		case PolygonMode::Line:
			glDrawElements(GL_LINES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		}
	}

	void OpenGLMesh::RenderAsInstance(const glm::vec3& position, BaseMaterial& material, const PolygonMode& mode) // Render without binding material
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		material.SetModelShaderProperties(position);

		switch (mode)
		{
		case PolygonMode::Triangle:
			glDrawElements(GL_TRIANGLES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		case PolygonMode::Line:
			glDrawElements(GL_LINES, _numTriangles, GL_UNSIGNED_INT, 0);
			break;
		}
	}

	void OpenGLMesh::SetMesh(BaseVertex* vertices, uint32_t vertexTypeSize, int numVertices, uint32_t* indices, int numIndices)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		glBufferData(GL_ARRAY_BUFFER, numVertices * vertexTypeSize, vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	
		_numTriangles = numIndices;
	}

	void OpenGLMesh::SetVertexProperties(BaseMaterial& material) 
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		material.Bind();
		material.SetVertexAttributes();
	}
}