#include <WillowVoxEngine/World/World.h>
#include <WillowVoxEngine/Rendering/OpenGLGraphicsAPI.h>
#include <WillowVoxEngine/Core/Logger.h>

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
		tex = new Texture("assets/block_map.png");
		tex->BindTexture(Texture::TEX00);
        chunkShader = new Shader("assets/chunk_vert.glsl", "assets/chunk_frag.glsl");
        chunkManager.terrainShader = chunkShader;
        chunkShader->Use();
        chunkShader->SetFloat("texMultiplier", 16.0f / tex->width);

        chunkManager.SetPlayerObj(mainCamera);

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
        OpenGLGraphicsAPI::EnableCullFace();
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