#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/World/ChunkVertex.h>
#include <vector>

namespace WillowVox
{
    Chunk::Chunk(Shader& shader)
    {
        mr = new MeshRenderer(shader);
    }

    Chunk::~Chunk()
    {
        delete mr;
    }

    void Chunk::GenerateChunk()
    {
        std::vector<ChunkVertex> vertices;
        vertices.reserve(24);
        std::vector<uint32_t> indices;
        indices.reserve(6);

        uint32_t currentVertex = 0;

        // North
        {
            vertices.emplace_back(1, 0, 0, 0, 0);
            vertices.emplace_back(0, 0, 0, 1, 0);
            vertices.emplace_back(1, 1, 0, 0, 1);
            vertices.emplace_back(0, 1, 0, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        // South
        {
            vertices.emplace_back(0, 0, 1, 0, 0);
            vertices.emplace_back(1, 0, 1, 1, 0);
            vertices.emplace_back(0, 1, 1, 0, 1);
            vertices.emplace_back(1, 1, 1, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        // West
        {
            vertices.emplace_back(0, 0, 0, 0, 0);
            vertices.emplace_back(0, 0, 1, 1, 0);
            vertices.emplace_back(0, 1, 0, 0, 1);
            vertices.emplace_back(0, 1, 1, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        // East
        {
            vertices.emplace_back(1, 0, 1, 0, 0);
            vertices.emplace_back(1, 0, 0, 1, 0);
            vertices.emplace_back(1, 1, 1, 0, 1);
            vertices.emplace_back(1, 1, 0, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        // Bottom
        {
            vertices.emplace_back(1, 0, 1, 0, 0);
            vertices.emplace_back(0, 0, 1, 1, 0);
            vertices.emplace_back(1, 0, 0, 0, 1);
            vertices.emplace_back(0, 0, 0, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        // Top
        {
            vertices.emplace_back(0, 1, 1, 0, 0);
            vertices.emplace_back(1, 1, 1, 1, 0);
            vertices.emplace_back(0, 1, 0, 0, 1);
            vertices.emplace_back(1, 1, 0, 1, 1);

            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 3);
            indices.emplace_back(currentVertex + 1);
            indices.emplace_back(currentVertex + 0);
            indices.emplace_back(currentVertex + 2);
            indices.emplace_back(currentVertex + 3);
            currentVertex += 4;
        }

        Mesh<ChunkVertex>* mesh = new Mesh<ChunkVertex>();
        mesh->SetMeshData(vertices, indices);
        mr->SetMesh(mesh, true);
    }

    void Chunk::Render()
    {
        mr->Render();
    }
}