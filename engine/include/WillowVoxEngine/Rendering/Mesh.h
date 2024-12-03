#pragma once

#include <WillowVoxEngine/Rendering/Shader.h>
#include <WillowVoxEngine/Rendering/BMesh.h>
#include <cstdint>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace WillowVox
{
    template <typename T> class Mesh : public BMesh
    {
    public:
        Mesh()
        {
            // Generate vertex array and vertex buffer
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // Enable vertex attributes
            T::SetShaderAttributes();
        }

        ~Mesh() override
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        void SetMeshData(std::vector<T>& vertices, std::vector<uint32_t>& indices)
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

        void SetMeshData(T* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount)
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

        void SetMeshData(T* vertices, uint32_t vertexCount, std::vector<uint32_t>& indices)
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

        void SetMeshData(std::vector<T>& vertices, uint32_t* indices, uint32_t indexCount)
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

        void Render(Shader& shader) override
        {
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, triCount, GL_UNSIGNED_INT, 0); // Error for some reason
        }

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        uint32_t triCount;
    };
}