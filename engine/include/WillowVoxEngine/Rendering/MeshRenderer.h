#pragma once

#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/Shader.h>

namespace WillowVox
{
    template <typename T> class MeshRenderer
    {
    public:
        MeshRenderer(Shader& shader) : shader(shader) {}
        MeshRenderer(Shader& shader, Mesh<T>* mesh) : shader(shader), mesh(mesh) {}

        ~MeshRenderer()
        {
            if (destroyMeshWhenDestroyed)
                delete this->mesh;
        }

        void SetShader(Shader& shader) { this->shader = shader; }
        void SetMesh(Mesh<T>* mesh, bool destroyMeshWhenDestroyed = false)
        {
            if (mesh != nullptr && this->destroyMeshWhenDestroyed)
                delete this->mesh;
            this->mesh = mesh;

            this->destroyMeshWhenDestroyed = destroyMeshWhenDestroyed;
        }

        void Render()
        {
            mesh->Render(shader);
        }

    private:
        Shader& shader;
        Mesh<T>* mesh;

        bool destroyMeshWhenDestroyed = false;
    };
}