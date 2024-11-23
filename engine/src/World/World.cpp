#include <WillowVoxEngine/World/World.h>

namespace WillowVox
{
    World::~World()
    {
        for (auto i : gameObjects)
        {
            delete i;
        }

        delete chunk;
    }

    void World::Start()
    {
        chunkShader = new Shader("assets/chunk_vert.glsl", "assets/chunk_frag.glsl");

        chunk = new Chunk(*chunkShader);
    }

    void World::Update()
    {

    }

    void World::Render()
    {
        glm::mat4 view = mainCamera->GetViewMatrix();
		glm::mat4 projection = mainCamera->GetProjectionMatrix();
		chunkShader->Use();
		chunkShader->SetMat4("view", view);
		chunkShader->SetMat4("projection", projection);
		chunkShader->SetVec3("model", glm::vec3(0, 0, 0));
        chunk->Render();
    }

    void World::AddMeshRenderer(MeshRenderer* mr)
    {
        meshRenderers.push_back(mr);
    }

    void World::AddGameObject(GameObject* gameObject)
    {
        gameObjects.push_back(gameObject);
    }
}