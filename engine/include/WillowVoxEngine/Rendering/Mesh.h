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

        void SetMeshData(std::vector<Vertex>& vertices);
        void SetMeshData(Vertex* vertices, uint32_t vertexCount);

        void Render(Shader& shader);

    private:
        unsigned int VAO;
        unsigned int VBO;

        uint32_t triCount;
    };
}