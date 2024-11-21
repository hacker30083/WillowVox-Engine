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
        ~MeshRenderer();

        void SetShader(Shader& shader);
        void SetMesh(Mesh<T>* mesh, bool destroyMeshWhenDestroyed = false);

        void Render();

    private:
        Shader& shader;
        Mesh<T>* mesh;

        bool destroyMeshWhenDestroyed = false;
    };
}