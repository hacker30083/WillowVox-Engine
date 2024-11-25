#include <WillowVoxEngine/World/ChunkManager.h>
#include <WillowVoxEngine/World/WorldGlobals.h>

namespace WillowVox
{
    ChunkManager::~ChunkManager()
    {
        delete chunk;
    }

    void ChunkManager::Start()
    {
        chunk = new Chunk(*terrainShader);

        uint16_t* data = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
        {
            data[i] = std::rand() % 2;
        }

        ChunkData* chunkData = new ChunkData(data);

        chunk->SetChunkData(chunkData);
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