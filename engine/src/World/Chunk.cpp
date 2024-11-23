#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/Vertex.h>

namespace WillowVox
{
    Chunk::Chunk(Shader& shader)
    {
        mr = new MeshRenderer(shader);

        Vertex vertices[] = {
			{ { -1.0f, -1.0f, -5.0f }, { 0.0f, 0.0f } },
			{ {  1.0f, -1.0f, -5.0f }, { 1.0f, 0.0f } },
			{ { -1.0f,  1.0f, -5.0f }, { 0.0f, 1.0f } },
			{ {  1.0f,  1.0f, -5.0f }, { 1.0f, 1.0f } },
		};
	
		uint32_t indices[] = {
			0, 1, 3,
			0, 2, 3
		};

        Mesh<Vertex>* mesh = new Mesh<Vertex>();
        mesh->SetMeshData(vertices, 4, indices, 6);
        mr->SetMesh(mesh, true);
    }

    Chunk::~Chunk()
    {
        delete mr;
    }

    void Chunk::Render()
    {
        mr->Render();
    }
}