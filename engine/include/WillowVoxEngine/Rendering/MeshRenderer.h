#pragma once

#include <WillowVoxEngine/Rendering/BMesh.h>
#include <WillowVoxEngine/Rendering/Shader.h>

namespace WillowVox
{
    class MeshRenderer
    {
    public:
        MeshRenderer(Shader& shader) : shader(shader) {}
        MeshRenderer(Shader& shader, BMesh* mesh) : shader(shader), mesh(mesh) {}

        ~MeshRenderer()
        {
            if (destroyMeshWhenDestroyed)
                delete this->mesh;
        }

        void SetShader(Shader& shader) { this->shader = shader; }
        void SetMesh(BMesh* mesh, bool destroyMeshWhenDestroyed = false)
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
        BMesh* mesh;

        bool destroyMeshWhenDestroyed = false;
    };
}