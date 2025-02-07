#include <WillowVox/world/Chunk.h>
#include <WillowVox/rendering/Mesh.h>
#include <WillowVox/world/WorldGlobals.h>
#include <WillowVox/core/Logger.h>
#include <WillowVox/resources/Blocks.h>
#include <WillowVox/core/Application.h>

namespace WillowVox
{
    Chunk::Chunk(BaseMaterial* solidMaterial, BaseMaterial* fluidMaterial, BaseMaterial* billboardMaterial, const glm::ivec3& chunkPos, const glm::vec3& worldPos)
        : _solidMaterial(solidMaterial), _fluidMaterial(fluidMaterial), _billboardMaterial(billboardMaterial), m_chunkPos(chunkPos), _worldPos(worldPos)
    {
        _solidMesh = new MeshRenderer(*solidMaterial);
        _fluidMesh = new MeshRenderer(*fluidMaterial);
        _billboardMesh = new MeshRenderer(*billboardMaterial);
    }

    Chunk::~Chunk()
    {
        delete _solidMesh;
        delete _fluidMesh;
        delete _billboardMesh;
    }

    void Chunk::GenerateChunkMeshData()
    {
        _solidVertices.clear();
        _solidIndices.clear();
        _fluidVertices.clear();
        _fluidIndices.clear();
        _billboardVertices.clear();
        _billboardIndices.clear();

        uint32_t currentSolidVertex = 0;
        uint32_t currentFluidVertex = 0;
        uint32_t currentBillboardVertex = 0;

        for (char x = 0; x < CHUNK_SIZE; x++)
        {
            for (char z = 0; z < CHUNK_SIZE; z++)
            {
                for (char y = 0; y < CHUNK_SIZE; y++)
                {
                    // If air, ignore
                    if (m_chunkData->GetBlock(x, y, z) == 0)
                        continue;

                    // Get block
                    Block& block = Blocks::GetBlock(m_chunkData->GetBlock(x, y, z));

                    // Get top block now for water animation
                    int topBlockId;
                    if (y < CHUNK_SIZE - 1)
                        topBlockId = m_chunkData->GetBlock(x, y + 1, z);
                    else
                        topBlockId = m_upData->GetBlock(x, 0, z);
                    Block& topBlock = Blocks::GetBlock(topBlockId);
                    char waterTopValue = topBlock.blockType == Block::TRANSPARENT ? 1 : 0;

                    if (block.blockType == Block::BILLBOARD)
                    {
                        _billboardVertices.emplace_back(x + .85355f, y + 0, z + .85355f, block.sideMinX, block.sideMinY);
                        _billboardVertices.emplace_back(x + .14645f, y + 0, z + .14645f, block.sideMaxX, block.sideMinY);
                        _billboardVertices.emplace_back(x + .85355f, y + 1, z + .85355f, block.sideMinX, block.sideMaxY);
                        _billboardVertices.emplace_back(x + .14645f, y + 1, z + .14645f, block.sideMaxX, block.sideMaxY);

                        _billboardIndices.emplace_back(currentBillboardVertex + 0);
                        _billboardIndices.emplace_back(currentBillboardVertex + 3);
                        _billboardIndices.emplace_back(currentBillboardVertex + 1);
                        _billboardIndices.emplace_back(currentBillboardVertex + 0);
                        _billboardIndices.emplace_back(currentBillboardVertex + 2);
                        _billboardIndices.emplace_back(currentBillboardVertex + 3);
                        currentBillboardVertex += 4;

                        _billboardVertices.emplace_back(x + .14645f, y + 0, z + .85355f, block.sideMinX, block.sideMinY);
                        _billboardVertices.emplace_back(x + .85355f, y + 0, z + .14645f, block.sideMaxX, block.sideMinY);
                        _billboardVertices.emplace_back(x + .14645f, y + 1, z + .85355f, block.sideMinX, block.sideMaxY);
                        _billboardVertices.emplace_back(x + .85355f, y + 1, z + .14645f, block.sideMaxX, block.sideMaxY);

                        _billboardIndices.emplace_back(currentBillboardVertex + 0);
                        _billboardIndices.emplace_back(currentBillboardVertex + 3);
                        _billboardIndices.emplace_back(currentBillboardVertex + 1);
                        _billboardIndices.emplace_back(currentBillboardVertex + 0);
                        _billboardIndices.emplace_back(currentBillboardVertex + 2);
                        _billboardIndices.emplace_back(currentBillboardVertex + 3);
                        currentBillboardVertex += 4;
                    }
                    else
                    {
                        // North
                        {
                            int nBlockId;
                            if (z > 0)
                                nBlockId = m_chunkData->GetBlock(x, y, z - 1);
                            else
                                nBlockId = m_northData->GetBlock(x, y, CHUNK_SIZE - 1);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMinX, block.sideMinY, 0, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMaxX, block.sideMinY, 0, 0);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMinX, block.sideMaxY, 0, waterTopValue);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMaxX, block.sideMaxY, 0, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMinX, block.sideMinY, 0);
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMaxX, block.sideMinY, 0);
                                    _solidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMinX, block.sideMaxY, 0);
                                    _solidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMaxX, block.sideMaxY, 0);

                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    _solidIndices.emplace_back(currentSolidVertex + 1);
                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 2);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // South
                        {
                            int nBlockId;
                            if (z < CHUNK_SIZE - 1)
                                nBlockId = m_chunkData->GetBlock(x, y, z + 1);
                            else
                                nBlockId = m_southData->GetBlock(x, y, 0);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMinX, block.sideMinY, 1, 0);
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMaxX, block.sideMinY, 1, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMinX, block.sideMaxY, 1, waterTopValue);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMaxX, block.sideMaxY, 1, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMinX, block.sideMinY, 1);
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMaxX, block.sideMinY, 1);
                                    _solidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMinX, block.sideMaxY, 1);
                                    _solidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMaxX, block.sideMaxY, 1);

                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    _solidIndices.emplace_back(currentSolidVertex + 1);
                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 2);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // East
                        {
                            int nBlockId;
                            if (x < CHUNK_SIZE - 1)
                                nBlockId = m_chunkData->GetBlock(x + 1, y, z);
                            else
                                nBlockId = m_eastData->GetBlock(0, y, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMinX, block.sideMinY, 3, 0);
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMaxX, block.sideMinY, 3, 0);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMinX, block.sideMaxY, 3, waterTopValue);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMaxX, block.sideMaxY, 3, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMinX, block.sideMinY, 3);
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMaxX, block.sideMinY, 3);
                                    _solidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMinX, block.sideMaxY, 3);
                                    _solidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMaxX, block.sideMaxY, 3);

                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    _solidIndices.emplace_back(currentSolidVertex + 1);
                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 2);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // West
                        {
                            int nBlockId;
                            if (x > 0)
                                nBlockId = m_chunkData->GetBlock(x - 1, y, z);
                            else
                                nBlockId = m_westData->GetBlock(CHUNK_SIZE - 1, y, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMinX, block.sideMinY, 2, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMaxX, block.sideMinY, 2, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMinX, block.sideMaxY, 2, waterTopValue);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMaxX, block.sideMaxY, 2, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMinX, block.sideMinY, 2);
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMaxX, block.sideMinY, 2);
                                    _solidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMinX, block.sideMaxY, 2);
                                    _solidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMaxX, block.sideMaxY, 2);

                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    _solidIndices.emplace_back(currentSolidVertex + 1);
                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 2);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // Bottom
                        {
                            int nBlockId;
                            if (y > 0)
                                nBlockId = m_chunkData->GetBlock(x, y - 1, z);
                            else
                                nBlockId = m_downData->GetBlock(x, CHUNK_SIZE - 1, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.bottomMinX, block.bottomMinY, 4, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.bottomMaxX, block.bottomMinY, 4, 0);
                                    _fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.bottomMinX, block.bottomMaxY, 4, 0);
                                    _fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.bottomMaxX, block.bottomMaxY, 4, 0);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 1, block.bottomMinX, block.bottomMinY, 4);
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 1, block.bottomMaxX, block.bottomMinY, 4);
                                    _solidVertices.emplace_back(x + 1, y + 0, z + 0, block.bottomMinX, block.bottomMaxY, 4);
                                    _solidVertices.emplace_back(x + 0, y + 0, z + 0, block.bottomMaxX, block.bottomMaxY, 4);

                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    _solidIndices.emplace_back(currentSolidVertex + 1);
                                    _solidIndices.emplace_back(currentSolidVertex + 0);
                                    _solidIndices.emplace_back(currentSolidVertex + 2);
                                    _solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // Top
                        {
                            if (block.blockType == Block::LIQUID)
                            {
                                if (topBlock.blockType != Block::LIQUID)
                                {
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMinX, block.topMinY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMaxX, block.topMinY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMinX, block.topMaxY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMaxX, block.topMaxY, 5, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;

                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMinX, block.topMinY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMaxX, block.topMinY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMinX, block.topMaxY, 5, waterTopValue);
                                    _fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMaxX, block.topMaxY, 5, waterTopValue);

                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    _fluidIndices.emplace_back(currentFluidVertex + 1);
                                    _fluidIndices.emplace_back(currentFluidVertex + 0);
                                    _fluidIndices.emplace_back(currentFluidVertex + 2);
                                    _fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                            }
                            else if (topBlock.blockType == Block::TRANSPARENT ||
                                topBlock.blockType == Block::LEAVES ||
                                topBlock.blockType == Block::BILLBOARD ||
                                topBlock.blockType == Block::LIQUID)
                            {
                                _solidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMinX, block.topMinY, 5);
                                _solidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMaxX, block.topMinY, 5);
                                _solidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMinX, block.topMaxY, 5);
                                _solidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMaxX, block.topMaxY, 5);

                                _solidIndices.emplace_back(currentSolidVertex + 0);
                                _solidIndices.emplace_back(currentSolidVertex + 3);
                                _solidIndices.emplace_back(currentSolidVertex + 1);
                                _solidIndices.emplace_back(currentSolidVertex + 0);
                                _solidIndices.emplace_back(currentSolidVertex + 2);
                                _solidIndices.emplace_back(currentSolidVertex + 3);
                                currentSolidVertex += 4;
                            }
                        }
                    }
                }
            }
        }
    }

    void Chunk::GenerateChunkMesh()
    {
        RenderingAPI& api = *RenderingAPI::m_renderingAPI;
        Mesh* sm = api.CreateMesh();
        Mesh* fm = api.CreateMesh();
        Mesh* bm = api.CreateMesh();
        sm->SetMesh(_solidVertices.data(), sizeof(ChunkVertex), _solidVertices.size(), _solidIndices.data(), _solidIndices.size());
        fm->SetMesh(_fluidVertices.data(), sizeof(FluidVertex), _fluidVertices.size(), _fluidIndices.data(), _fluidIndices.size());
        bm->SetMesh(_billboardVertices.data(), sizeof(Vertex), _billboardVertices.size(), _billboardIndices.data(), _billboardIndices.size());
        _solidMesh->SetMesh(sm, true);
        _fluidMesh->SetMesh(fm, true);
        _billboardMesh->SetMesh(bm, true);

        _solidVertices.clear();
        _solidIndices.clear();

        _fluidVertices.clear();
        _fluidIndices.clear();

        _billboardVertices.clear();
        _billboardIndices.clear();
    }

    void Chunk::RenderSolid(const glm::mat4& view, const glm::mat4& projection)
    {
        if (!m_ready)
        {
            GenerateChunkMesh();
            m_ready = true;
        }

        _solidMesh->Render(_worldPos);

        RenderingAPI& api = *RenderingAPI::m_renderingAPI;
        api.SetCullFace(false);
        _billboardMesh->Render(_worldPos);
        api.SetCullFace(true);
    }

    void Chunk::RenderTransparent()
    {
        if (!m_ready)
        {
            GenerateChunkMesh();
            m_ready = true;
        }

        _fluidMesh->Render(_worldPos);
    }

    uint16_t Chunk::GetBlockIdAtPos(int x, int y, int z)
    {
        return m_chunkData->GetBlock(x, y, z);
    }

    void Chunk::SetBlock(int x, int y, int z, uint16_t block)
    {
        m_chunkData->SetBlock(x, y, z, block);
        GenerateChunkMeshData();
        GenerateChunkMesh();

        if (x == 0)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x - 1, m_chunkPos.y, m_chunkPos.z)->ReloadChunk();
        if (x == CHUNK_SIZE - 1)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x + 1, m_chunkPos.y, m_chunkPos.z)->ReloadChunk();
        if (y == 0)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x, m_chunkPos.y - 1, m_chunkPos.z)->ReloadChunk();
        if (y == CHUNK_SIZE - 1)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x, m_chunkPos.y + 1, m_chunkPos.z)->ReloadChunk();
        if (z == 0)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x, m_chunkPos.y, m_chunkPos.z - 1)->ReloadChunk();
        if (z == CHUNK_SIZE - 1)
            ChunkManager::m_instance->GetChunk(m_chunkPos.x, m_chunkPos.y, m_chunkPos.z + 1)->ReloadChunk();
    }

    void Chunk::ReloadChunk()
    {
        GenerateChunkMeshData();
        GenerateChunkMesh();
    }
}