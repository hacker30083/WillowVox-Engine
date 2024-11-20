#include <WillowVoxEngine/Rendering/MeshRenderer.h>

namespace WillowVox
{
    MeshRenderer::~MeshRenderer()
    {
        if (destroyMeshWhenDestroyed)
            delete this->mesh;
    }

    void MeshRenderer::SetShader(Shader& shader)
    {
        this->shader = shader;
    }

    void MeshRenderer::SetMesh(Mesh* mesh, bool destroyMeshWhenDestroyed)
    {
        if (mesh != nullptr && this->destroyMeshWhenDestroyed)
            delete this->mesh;
        this->mesh = mesh;

        this->destroyMeshWhenDestroyed = destroyMeshWhenDestroyed;
    }

    void MeshRenderer::Render()
    {
        mesh->Render(shader);
    }
}