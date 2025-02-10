#include <WillowVox/world/World.h>
#include <WillowVox/core/Application.h>
#include <WillowVox/rendering/RenderingAPI.h>
#include <WillowVox/core/Logger.h>
#include <WillowVox/rendering/engine-default/ChunkSolidMaterial.h>
#include <WillowVox/rendering/engine-default/ChunkFluidMaterial.h>
#include <WillowVox/rendering/engine-default/TextureMaterial.h>

namespace WillowVox
{
    World::~World()
    {
        delete m_chunkManager;
    }

    void World::Start()
    {
        RenderingAPI& api = *RenderingAPI::m_renderingAPI;
        _tex = api.CreateTexture("assets/sprites/block_map.png");
        _tex->BindTexture(Texture::TEX00);

        _solidShader = api.CreateShader("assets/shaders/chunk-shaders/chunk_solid_vert.glsl", "assets/shaders/chunk-shaders/chunk_solid_frag.glsl");
        _solidMaterial = new ChunkSolidMaterial(_solidShader, _tex);
        m_chunkManager->m_solidMaterial = _solidMaterial;
        _solidShader->Bind();
        _solidShader->SetFloat("texMultiplier", 16.0f / _tex->m_width);

        _fluidShader = api.CreateShader("assets/shaders/chunk-shaders/chunk_fluid_vert.glsl", "assets/shaders/chunk-shaders/chunk_fluid_frag.glsl");
        _fluidMaterial = new ChunkFluidMaterial(_fluidShader, _tex);
        m_chunkManager->m_fluidMaterial = _fluidMaterial;
        _fluidShader->Bind();
        _fluidShader->SetFloat("texMultiplier", 16.0f / _tex->m_width);

        _billboardShader = api.CreateShader("assets/shaders/chunk-shaders/chunk_billboard_vert.glsl", "assets/shaders/chunk-shaders/chunk_billboard_frag.glsl");
        _billboardMaterial = new TextureMaterial(_billboardShader, _tex);
        m_chunkManager->m_billboardMaterial = _billboardMaterial;
        _billboardShader->Bind();
        _billboardShader->SetFloat("texMultiplier", 16.0f / _tex->m_width);

        m_chunkManager->SetPlayerObj(m_mainCamera);

        m_chunkManager->Start();
    }

    void World::Update()
    {
        m_chunkManager->Update();
    }

    void World::Render()
    {
        _fluidShader->Bind();
        _fluidShader->SetFloat("time", RenderingAPI::m_renderingAPI->GetTime());
        m_chunkManager->Render(*m_mainCamera);
    }
}