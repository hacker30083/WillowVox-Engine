#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/Rendering/Mesh.h>
#include <WillowVoxEngine/World/WorldGlobals.h>
#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/Resources/Blocks.h>

namespace WillowVox
{
    Chunk::Chunk(Shader& shader, glm::ivec3 chunkPos, glm::vec3 worldPos)
        : shader(shader), chunkPos(chunkPos), worldPos(worldPos)
    {
        mr = new MeshRenderer(shader);
    }

    Chunk::~Chunk()
    {
        delete mr;
    }

    void Chunk::GenerateChunkMeshData()
    {
        vertices.clear();
        indices.clear();

        uint32_t currentVertex = 0;
        
        for (char x = 0; x < CHUNK_SIZE; x++)
        {
            for (char z = 0; z < CHUNK_SIZE; z++)
            {
                for (char y = 0; y < CHUNK_SIZE; y++)
                {
                    if (chunkData->GetBlock(x, y, z) == 0)
                        continue;

                    Block& block = Blocks::GetBlock(chunkData->GetBlock(x, y, z));
                    
                    // North
                    {
                        int nBlock;
                        if (z > 0)
                            nBlock = chunkData->GetBlock(x, y, z - 1);
                        else
                            nBlock = northData->GetBlock(x, y, CHUNK_SIZE - 1);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 0, block.sideMinX, block.sideMinY);
                            vertices.emplace_back(x + 0, y + 0, z + 0, block.sideMaxX, block.sideMinY);
                            vertices.emplace_back(x + 1, y + 1, z + 0, block.sideMinX, block.sideMaxY);
                            vertices.emplace_back(x + 0, y + 1, z + 0, block.sideMaxX, block.sideMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // South
                    {
                        int nBlock;
                        if (z < CHUNK_SIZE - 1)
                            nBlock = chunkData->GetBlock(x, y, z + 1);
                        else
                            nBlock = southData->GetBlock(x, y, 0);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 0, y + 0, z + 1, block.sideMinX, block.sideMinY);
                            vertices.emplace_back(x + 1, y + 0, z + 1, block.sideMaxX, block.sideMinY);
                            vertices.emplace_back(x + 0, y + 1, z + 1, block.sideMinX, block.sideMaxY);
                            vertices.emplace_back(x + 1, y + 1, z + 1, block.sideMaxX, block.sideMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // East
                    {
                        int nBlock;
                        if (x < CHUNK_SIZE - 1)
                            nBlock = chunkData->GetBlock(x + 1, y, z);
                        else
                            nBlock = eastData->GetBlock(0, y, z);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 1, block.sideMinX, block.sideMinY);
                            vertices.emplace_back(x + 1, y + 0, z + 0, block.sideMaxX, block.sideMinY);
                            vertices.emplace_back(x + 1, y + 1, z + 1, block.sideMinX, block.sideMaxY);
                            vertices.emplace_back(x + 1, y + 1, z + 0, block.sideMaxX, block.sideMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // West
                    {
                        int nBlock;
                        if (x > 0)
                            nBlock = chunkData->GetBlock(x - 1, y, z);
                        else
                            nBlock = westData->GetBlock(CHUNK_SIZE - 1, y, z);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 0, y + 0, z + 0, block.sideMinX, block.sideMinY);
                            vertices.emplace_back(x + 0, y + 0, z + 1, block.sideMaxX, block.sideMinY);
                            vertices.emplace_back(x + 0, y + 1, z + 0, block.sideMinX, block.sideMaxY);
                            vertices.emplace_back(x + 0, y + 1, z + 1, block.sideMaxX, block.sideMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // Top
                    {
                        int nBlock;
                        if (y < CHUNK_SIZE - 1)
                            nBlock = chunkData->GetBlock(x, y + 1, z);
                        else
                            nBlock = upData->GetBlock(x, 0, z);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 0, y + 1, z + 1, block.topMinX, block.topMinY);
                            vertices.emplace_back(x + 1, y + 1, z + 1, block.topMaxX, block.topMinY);
                            vertices.emplace_back(x + 0, y + 1, z + 0, block.topMinX, block.topMaxY);
                            vertices.emplace_back(x + 1, y + 1, z + 0, block.topMaxX, block.topMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }

                    // Bottom
                    {
                        int nBlock;
                        if (y > 0)
                            nBlock = chunkData->GetBlock(x, y - 1, z);
                        else
                            nBlock = downData->GetBlock(x, CHUNK_SIZE - 1, z);

                        if (nBlock == 0)
                        {
                            vertices.emplace_back(x + 1, y + 0, z + 1, block.bottomMinX, block.bottomMinY);
                            vertices.emplace_back(x + 0, y + 0, z + 1, block.bottomMaxX, block.bottomMinY);
                            vertices.emplace_back(x + 1, y + 0, z + 0, block.bottomMinX, block.bottomMaxY);
                            vertices.emplace_back(x + 0, y + 0, z + 0, block.bottomMaxX, block.bottomMaxY);

                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 3);
                            indices.emplace_back(currentVertex + 1);
                            indices.emplace_back(currentVertex + 0);
                            indices.emplace_back(currentVertex + 2);
                            indices.emplace_back(currentVertex + 3);
                            currentVertex += 4;
                        }
                    }
                }
            }
        }
    }

    void Chunk::GenerateChunkMesh()
    {
        Mesh<ChunkVertex>* mesh = new Mesh<ChunkVertex>();
        mesh->SetMeshData(vertices, indices);
        mr->SetMesh(mesh, true);

        vertices.clear();
        indices.clear();
    }

    void Chunk::Render()
    {
        if (!ready)
        {
            GenerateChunkMesh();
            ready = true;
        }

		shader.SetVec3("model", worldPos);
        mr->Render();
    }
}