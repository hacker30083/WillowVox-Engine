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

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

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
        glDeleteBuffers(1, &EBO);
    }

    
    void Mesh::SetMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indices.size();

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        
    }

    void Mesh::SetMeshData(Vertex* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indexCount;

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    void Mesh::SetMeshData(Vertex* vertices, uint32_t vertexCount, std::vector<uint32_t>& indices)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indices.size();

        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    }

    void Mesh::SetMeshData(std::vector<Vertex>& vertices, uint32_t* indices, uint32_t indexCount)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indexCount;

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    void Mesh::Render(Shader& shader)
    {
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, triCount, GL_UNSIGNED_INT, 0);
    }
}