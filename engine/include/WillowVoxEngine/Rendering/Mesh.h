#pragma once

#include <WillowVoxEngine/Rendering/Vertex.h>
#include <WillowVoxEngine/Rendering/Shader.h>
#include <vector>

namespace WillowVox
{
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        void SetMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
        void SetMeshData(Vertex* vertices, uint32_t vertexCount, uint32_t* indices, uint32_t indexCount);

        void SetMeshData(Vertex* vertices, uint32_t vertexCount, std::vector<uint32_t>& indices);
        void SetMeshData(std::vector<Vertex>& vertices, uint32_t* indices, uint32_t indexCount);

        void Render(Shader& shader);

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        uint32_t triCount;
    };
}