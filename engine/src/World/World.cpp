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

        solidShader = new Shader("assets/chunk_solid_vert.glsl", "assets/chunk_solid_frag.glsl");
        chunkManager.solidShader = solidShader;
        solidShader->Use();
        solidShader->SetFloat("texMultiplier", 16.0f / tex->width);

        fluidShader = new Shader("assets/chunk_fluid_vert.glsl", "assets/chunk_fluid_frag.glsl");
        chunkManager.fluidShader = fluidShader;
        fluidShader->Use();
        fluidShader->SetFloat("texMultiplier", 16.0f / tex->width);

        billboardShader = new Shader("assets/chunk_billboard_vert.glsl", "assets/chunk_billboard_frag.glsl");
        chunkManager.billboardShader = billboardShader;
        billboardShader->Use();
        billboardShader->SetFloat("texMultiplier", 16.0f / tex->width);

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
        fluidShader->SetFloat("time", OpenGLGraphicsAPI::GetTime());
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