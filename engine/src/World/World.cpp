#include <WillowVoxEngine/World/World.h>

namespace WillowVox
{
    void World::Start()
    {
        chunkShader = new Shader("assets/chunk_vert.glsl", "assets/chunk_frag.glsl");

        chunk = new Chunk(*chunkShader);
    }

    void World::Update()
    {

    }

    void World::Render(Camera& camera)
    {
        glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();
		chunkShader->Use();
		chunkShader->SetMat4("view", view);
		chunkShader->SetMat4("projection", projection);
		chunkShader->SetVec3("model", glm::vec3(0, 0, 0));
        chunk->Render();
    }
}