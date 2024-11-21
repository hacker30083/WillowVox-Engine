#include <WillowVoxEngine/Rendering/MeshRenderer.h>

namespace WillowVox
{
    template <typename T> MeshRenderer<T>::~MeshRenderer()
    {
        if (destroyMeshWhenDestroyed)
            delete this->mesh;
    }

    template <typename T> void MeshRenderer<T>::SetShader(Shader& shader)
    {
        this->shader = shader;
    }

    template <typename T> void MeshRenderer<T>::SetMesh(Mesh<T>* mesh, bool destroyMeshWhenDestroyed)
    {
        if (mesh != nullptr && this->destroyMeshWhenDestroyed)
            delete this->mesh;
        this->mesh = mesh;

        this->destroyMeshWhenDestroyed = destroyMeshWhenDestroyed;
    }

    template <typename T> void MeshRenderer<T>::Render()
    {
        mesh->Render(shader);
    }
}