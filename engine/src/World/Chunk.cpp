#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/World/WorldGlobals.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Resources/Blocks.h>

namespace WillowVox
{
    Chunk::Chunk(Shader& solidShader, Shader& fluidShader, Shader& billboardShader, glm::ivec3 chunkPos, glm::vec3 worldPos)
        : solidShader(solidShader), fluidShader(fluidShader), billboardShader(billboardShader), chunkPos(chunkPos), worldPos(worldPos)
    {
        solidMeshRenderer = new MeshRenderer(solidShader);
        fluidMeshRenderer = new MeshRenderer(fluidShader);
        billboardMeshRenderer = new MeshRenderer(billboardShader);
    }

    Chunk::~Chunk()
    {
        delete solidMeshRenderer;
        delete fluidMeshRenderer;
        delete billboardMeshRenderer;
    }

    void Chunk::GenerateChunkMeshData()
    {
        solidVertices.clear();
        solidIndices.clear();
        fluidVertices.clear();
        fluidIndices.clear();
        billboardVertices.clear();
        billboardIndices.clear();

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
                    if (chunkData->GetBlock(x, y, z) == 0)
                        continue;

                    // Get block
                    Block& block = Blocks::GetBlock(chunkData->GetBlock(x, y, z));
                    
                    // Get top block now for water animation
                    int topBlockId;
                    if (y < CHUNK_SIZE - 1)
                        topBlockId = chunkData->GetBlock(x, y + 1, z);
                    else
                        topBlockId = upData->GetBlock(x, 0, z);
                    Block& topBlock = Blocks::GetBlock(topBlockId);
                    char waterTopValue = topBlock.blockType == Block::TRANSPARENT ? 1 : 0;
                    
                    if (block.blockType == Block::BILLBOARD)
                    {
                        billboardVertices.emplace_back(x + .85355f, y + 0, z + .85355f, block.sideMinX, block.sideMinY);
                        billboardVertices.emplace_back(x + .14645f, y + 0, z + .14645f, block.sideMaxX, block.sideMinY);
                        billboardVertices.emplace_back(x + .85355f, y + 1, z + .85355f, block.sideMinX, block.sideMaxY);
                        billboardVertices.emplace_back(x + .14645f, y + 1, z + .14645f, block.sideMaxX, block.sideMaxY);

                        billboardIndices.emplace_back(currentBillboardVertex + 0);
                        billboardIndices.emplace_back(currentBillboardVertex + 3);
                        billboardIndices.emplace_back(currentBillboardVertex + 1);
                        billboardIndices.emplace_back(currentBillboardVertex + 0);
                        billboardIndices.emplace_back(currentBillboardVertex + 2);
                        billboardIndices.emplace_back(currentBillboardVertex + 3);
                        currentBillboardVertex += 4;

                        billboardVertices.emplace_back(x + .14645f, y + 0, z + .85355f, block.sideMinX, block.sideMinY);
                        billboardVertices.emplace_back(x + .85355f, y + 0, z + .14645f, block.sideMaxX, block.sideMinY);
                        billboardVertices.emplace_back(x + .14645f, y + 1, z + .85355f, block.sideMinX, block.sideMaxY);
                        billboardVertices.emplace_back(x + .85355f, y + 1, z + .14645f, block.sideMaxX, block.sideMaxY);

                        billboardIndices.emplace_back(currentBillboardVertex + 0);
                        billboardIndices.emplace_back(currentBillboardVertex + 3);
                        billboardIndices.emplace_back(currentBillboardVertex + 1);
                        billboardIndices.emplace_back(currentBillboardVertex + 0);
                        billboardIndices.emplace_back(currentBillboardVertex + 2);
                        billboardIndices.emplace_back(currentBillboardVertex + 3);
                        currentBillboardVertex += 4;
                    }
                    else
                    {
                        // North
                        {
                            int nBlockId;
                            if (z > 0)
                                nBlockId = chunkData->GetBlock(x, y, z - 1);
                            else
                                nBlockId = northData->GetBlock(x, y, CHUNK_SIZE - 1);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMinX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMaxX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMinX, block.sideMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMaxX, block.sideMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    solidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMinX, block.sideMinY);
                                    solidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMaxX, block.sideMinY);
                                    solidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMinX, block.sideMaxY);
                                    solidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMaxX, block.sideMaxY);

                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    solidIndices.emplace_back(currentSolidVertex + 1);
                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 2);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // South
                        {
                            int nBlockId;
                            if (z < CHUNK_SIZE - 1)
                                nBlockId = chunkData->GetBlock(x, y, z + 1);
                            else
                                nBlockId = southData->GetBlock(x, y, 0);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMinX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMaxX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMinX, block.sideMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMaxX, block.sideMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    solidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMinX, block.sideMinY);
                                    solidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMaxX, block.sideMinY);
                                    solidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMinX, block.sideMaxY);
                                    solidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMaxX, block.sideMaxY);

                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    solidIndices.emplace_back(currentSolidVertex + 1);
                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 2);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // East
                        {
                            int nBlockId;
                            if (x < CHUNK_SIZE - 1)
                                nBlockId = chunkData->GetBlock(x + 1, y, z);
                            else
                                nBlockId = eastData->GetBlock(0, y, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMinX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMaxX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMinX, block.sideMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMaxX, block.sideMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    solidVertices.emplace_back(x + 1, y + 0, z + 1, block.sideMinX, block.sideMinY);
                                    solidVertices.emplace_back(x + 1, y + 0, z + 0, block.sideMaxX, block.sideMinY);
                                    solidVertices.emplace_back(x + 1, y + 1, z + 1, block.sideMinX, block.sideMaxY);
                                    solidVertices.emplace_back(x + 1, y + 1, z + 0, block.sideMaxX, block.sideMaxY);

                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    solidIndices.emplace_back(currentSolidVertex + 1);
                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 2);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // West
                        {
                            int nBlockId;
                            if (x > 0)
                                nBlockId = chunkData->GetBlock(x - 1, y, z);
                            else
                                nBlockId = westData->GetBlock(CHUNK_SIZE - 1, y, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMinX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMaxX, block.sideMinY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMinX, block.sideMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMaxX, block.sideMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    solidVertices.emplace_back(x + 0, y + 0, z + 0, block.sideMinX, block.sideMinY);
                                    solidVertices.emplace_back(x + 0, y + 0, z + 1, block.sideMaxX, block.sideMinY);
                                    solidVertices.emplace_back(x + 0, y + 1, z + 0, block.sideMinX, block.sideMaxY);
                                    solidVertices.emplace_back(x + 0, y + 1, z + 1, block.sideMaxX, block.sideMaxY);

                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    solidIndices.emplace_back(currentSolidVertex + 1);
                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 2);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    currentSolidVertex += 4;
                                }
                            }
                        }

                        // Bottom
                        {
                            int nBlockId;
                            if (y > 0)
                                nBlockId = chunkData->GetBlock(x, y - 1, z);
                            else
                                nBlockId = downData->GetBlock(x, CHUNK_SIZE - 1, z);

                            Block& nBlock = Blocks::GetBlock(nBlockId);

                            if (nBlock.blockType == Block::TRANSPARENT ||
                                nBlock.blockType == Block::LEAVES ||
                                nBlock.blockType == Block::BILLBOARD ||
                                (nBlock.blockType == Block::LIQUID && block.blockType != Block::LIQUID))
                            {
                                if (block.blockType == Block::LIQUID)
                                {
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 1, block.bottomMinX, block.bottomMinY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 1, block.bottomMaxX, block.bottomMinY, 0);
                                    fluidVertices.emplace_back(x + 1, y + 0, z + 0, block.bottomMinX, block.bottomMaxY, 0);
                                    fluidVertices.emplace_back(x + 0, y + 0, z + 0, block.bottomMaxX, block.bottomMaxY, 0);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                                else
                                {
                                    solidVertices.emplace_back(x + 1, y + 0, z + 1, block.bottomMinX, block.bottomMinY);
                                    solidVertices.emplace_back(x + 0, y + 0, z + 1, block.bottomMaxX, block.bottomMinY);
                                    solidVertices.emplace_back(x + 1, y + 0, z + 0, block.bottomMinX, block.bottomMaxY);
                                    solidVertices.emplace_back(x + 0, y + 0, z + 0, block.bottomMaxX, block.bottomMaxY);

                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
                                    solidIndices.emplace_back(currentSolidVertex + 1);
                                    solidIndices.emplace_back(currentSolidVertex + 0);
                                    solidIndices.emplace_back(currentSolidVertex + 2);
                                    solidIndices.emplace_back(currentSolidVertex + 3);
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
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMinX, block.topMinY, waterTopValue);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMaxX, block.topMinY, waterTopValue);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMinX, block.topMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMaxX, block.topMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                    
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMinX, block.topMinY, waterTopValue);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMaxX, block.topMinY, waterTopValue);
                                    fluidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMinX, block.topMaxY, waterTopValue);
                                    fluidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMaxX, block.topMaxY, waterTopValue);

                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    fluidIndices.emplace_back(currentFluidVertex + 1);
                                    fluidIndices.emplace_back(currentFluidVertex + 0);
                                    fluidIndices.emplace_back(currentFluidVertex + 2);
                                    fluidIndices.emplace_back(currentFluidVertex + 3);
                                    currentFluidVertex += 4;
                                }
                            }
                            else if (topBlock.blockType == Block::TRANSPARENT ||
                                topBlock.blockType == Block::LEAVES ||
                                topBlock.blockType == Block::BILLBOARD ||
                                topBlock.blockType == Block::LIQUID)
                            {
                                solidVertices.emplace_back(x + 0, y + 1, z + 1, block.topMinX, block.topMinY);
                                solidVertices.emplace_back(x + 1, y + 1, z + 1, block.topMaxX, block.topMinY);
                                solidVertices.emplace_back(x + 0, y + 1, z + 0, block.topMinX, block.topMaxY);
                                solidVertices.emplace_back(x + 1, y + 1, z + 0, block.topMaxX, block.topMaxY);

                                solidIndices.emplace_back(currentSolidVertex + 0);
                                solidIndices.emplace_back(currentSolidVertex + 3);
                                solidIndices.emplace_back(currentSolidVertex + 1);
                                solidIndices.emplace_back(currentSolidVertex + 0);
                                solidIndices.emplace_back(currentSolidVertex + 2);
                                solidIndices.emplace_back(currentSolidVertex + 3);
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
        Mesh<ChunkVertex>* solidMesh = new Mesh<ChunkVertex>();
        solidMesh->SetMeshData(solidVertices, solidIndices);
        solidMeshRenderer->SetMesh(solidMesh, true);

        Mesh<FluidVertex>* fluidMesh = new Mesh<FluidVertex>();
        fluidMesh->SetMeshData(fluidVertices, fluidIndices);
        fluidMeshRenderer->SetMesh(fluidMesh, true);

        Mesh<BillboardVertex>* billboardMesh = new Mesh<BillboardVertex>();
        billboardMesh->SetMeshData(billboardVertices, billboardIndices);
        billboardMeshRenderer->SetMesh(billboardMesh, true);

        solidVertices.clear();
        solidIndices.clear();

        fluidVertices.clear();
        fluidIndices.clear();

        billboardVertices.clear();
        billboardIndices.clear();
    }

    void Chunk::RenderSolid()
    {
        if (!ready)
        {
            GenerateChunkMesh();
            ready = true;
        }

        solidShader.Use();
		solidShader.SetVec3("model", worldPos);
        solidMeshRenderer->Render();

        OpenGLGraphicsAPI::DisableCullFace();
        billboardShader.Use();
		billboardShader.SetVec3("model", worldPos);
        billboardMeshRenderer->Render();
        OpenGLGraphicsAPI::EnableCullFace();
    }

    void Chunk::RenderTransparent()
    {
        if (!ready)
        {
            GenerateChunkMesh();
            ready = true;
        }

        fluidShader.Use();
		fluidShader.SetVec3("model", worldPos);
        fluidMeshRenderer->Render();
    }
}