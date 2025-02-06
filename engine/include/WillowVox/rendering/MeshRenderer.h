#pragma once

#include <WillowVox/rendering/Mesh.h>
#include <WillowVox/rendering/BaseMaterial.h>

namespace WillowVox
{
    class MeshRenderer
    {
    public:
        MeshRenderer(BaseMaterial& material) : _material(material) {}
        MeshRenderer(BaseMaterial& material, Mesh* mesh) : _material(material), _mesh(mesh) {
            _mesh->SetVertexProperties(_material);
        }

        ~MeshRenderer()
        {
            if (destroyMeshWhenDestroyed)
                delete _mesh;
        }

        void SetShader(BaseMaterial& material) { _material = material; }
        void SetMesh(Mesh* mesh, bool destroyMeshWhenDestroyed = false)
        {
            if (_mesh != nullptr && this->destroyMeshWhenDestroyed)
                delete _mesh;
            _mesh = mesh;
            _mesh->SetVertexProperties(_material);

            this->destroyMeshWhenDestroyed = destroyMeshWhenDestroyed;
        }

        void Render(const glm::vec3& position, const PolygonMode& mode = PolygonMode::Triangle)
        {
            _mesh->Render(position, _material, mode);
        }
        void Render(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& position, const PolygonMode& mode = PolygonMode::Triangle)
        {
            _mesh->Render(view, projection, position, _material, mode);
        }

    private:
        BaseMaterial& _material;
        Mesh* _mesh;

        bool destroyMeshWhenDestroyed = false;
    };
}