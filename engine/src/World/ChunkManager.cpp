#include <WillowVoxEngine/World/ChunkManager.h>

namespace WillowVox
{
    ChunkManager::~ChunkManager()
    {
        delete chunk;
    }

    void ChunkManager::Start()
    {
        chunk = new Chunk(*terrainShader);
        chunk->GenerateChunk();
    }

    void ChunkManager::Update()
    {

    }

    void ChunkManager::ChunkThreadUpdate()
    {

    }

    void ChunkManager::Render(Camera& camera)
    {
        glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();
		terrainShader->Use();
		terrainShader->SetMat4("view", view);
		terrainShader->SetMat4("projection", projection);
		terrainShader->SetVec3("model", glm::vec3(0, 0, 0));
        chunk->Render();
    }
}