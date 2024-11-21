#include <WillowVoxEngine/Rendering/Mesh.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace WillowVox
{
    template <typename T> Mesh<T>::Mesh()
    {
        // Generate vertex array and vertex buffer
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Enable vertex attributes
        T.SetShaderAttributes();
    }

    template <typename T> Mesh<T>::~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    
    template <typename T> void Mesh<T>::SetMeshData(std::vector<T>& vertices, std::vector<uint32_t>& indices)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indices.size();

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        
    }

    template <typename T> void Mesh<T>::SetMeshData(T* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indexCount;

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(T), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    template <typename T> void Mesh<T>::SetMeshData(T* vertices, uint32_t vertexCount, std::vector<uint32_t>& indices)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indices.size();

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(T), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    }

    template <typename T> void Mesh<T>::SetMeshData(std::vector<T>& vertices, uint32_t* indices, uint32_t indexCount)
    {
        // Bind buffers
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        triCount = indexCount;

        // Buffer data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    template <typename T> void Mesh<T>::Render(Shader& shader)
    {
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, triCount, GL_UNSIGNED_INT, 0);
    }
}