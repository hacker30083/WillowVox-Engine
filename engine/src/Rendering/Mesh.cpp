#include <WillowVoxEngine/Rendering/Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace WillowVox
{
    Mesh::Mesh()
    {
        // Generate vertex array and vertex buffer
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // Enable vertex attributes
        // TODO: Allow for different types of Vertex classes with different attributes
		glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Mesh::SetMeshData(std::vector<Vertex>& vertices)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        triCount = vertices.size();
        glBufferData(GL_ARRAY_BUFFER, triCount * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    void Mesh::SetMeshData(Vertex* vertices, uint32_t vertexCount)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        triCount = vertexCount;
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
    }

    void Mesh::Render(Shader& shader)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glDrawArrays(GL_TRIANGLES, 0, triCount);
    }
}