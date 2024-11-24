#include <WillowVoxEngine/World/World.h>

namespace WillowVox
{
    World::~World()
    {
        for (auto i : gameObjects)
        {
            delete i;
        }
    }

    void World::Start()
    {
        chunkShader = new Shader("assets/chunk_vert.glsl", "assets/chunk_frag.glsl");
        chunkManager.terrainShader = chunkShader;

        chunkManager.Start();

        for (auto i : gameObjects)
        {
            i->Start();
        }
    }

    void World::Update()
    {
        chunkManager.Update();

        for (auto i : gameObjects)
        {
            i->Update();
        }
    }

    void World::Render()
    {
        chunkManager.Render(*mainCamera);
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