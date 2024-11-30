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
                    if (chunkData->GetBlock(x, y, z) == 0)
                        continue;

                    Block& block = Blocks::GetBlock(chunkData->GetBlock(x, y, z));
                    
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
                            int nBlock;
                            if (z > 0)
                                nBlock = chunkData->GetBlock(x, y, z - 1);
                            else
                                nBlock = northData->GetBlock(x, y, CHUNK_SIZE - 1);

                            if (nBlock != Block::TRANSPARENT)
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

                        // South
                        {
                            int nBlock;
                            if (z < CHUNK_SIZE - 1)
                                nBlock = chunkData->GetBlock(x, y, z + 1);
                            else
                                nBlock = southData->GetBlock(x, y, 0);

                            if (nBlock != Block::TRANSPARENT)
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

                        // East
                        {
                            int nBlock;
                            if (x < CHUNK_SIZE - 1)
                                nBlock = chunkData->GetBlock(x + 1, y, z);
                            else
                                nBlock = eastData->GetBlock(0, y, z);

                            if (nBlock != Block::TRANSPARENT)
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

                        // West
                        {
                            int nBlock;
                            if (x > 0)
                                nBlock = chunkData->GetBlock(x - 1, y, z);
                            else
                                nBlock = westData->GetBlock(CHUNK_SIZE - 1, y, z);

                            if (nBlock != Block::TRANSPARENT)
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

                        // Top
                        {
                            int nBlock;
                            if (y < CHUNK_SIZE - 1)
                                nBlock = chunkData->GetBlock(x, y + 1, z);
                            else
                                nBlock = upData->GetBlock(x, 0, z);

                            if (nBlock != Block::TRANSPARENT)
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

                        // Bottom
                        {
                            int nBlock;
                            if (y > 0)
                                nBlock = chunkData->GetBlock(x, y - 1, z);
                            else
                                nBlock = downData->GetBlock(x, CHUNK_SIZE - 1, z);

                            if (nBlock != Block::TRANSPARENT)
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

		fluidShader.SetVec3("model", worldPos);
        fluidMeshRenderer->Render();
    }
}