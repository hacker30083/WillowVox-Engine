#pragma once

#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/Rendering/Shader.h>

namespace WillowVox
{
    class MeshRenderer
    {
    public:
        MeshRenderer(Shader& shader) : shader(shader) {}
        MeshRenderer(Shader& shader, Mesh* mesh) : shader(shader), mesh(mesh) {}
        ~MeshRenderer();

        void SetShader(Shader& shader);
        void SetMesh(Mesh* mesh, bool destroyMeshWhenDestroyed = false);

        void Render();

    private:
        Shader& shader;
        Mesh* mesh;

        bool destroyMeshWhenDestroyed = false;
    };
}