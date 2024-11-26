#include <WillowVoxEngine/World/ChunkManager.h>
#include <WillowVoxEngine/World/WorldGlobals.h>
#include <WillowVoxEngine/Core/Logger.h>

namespace WillowVox
{
    ChunkManager::~ChunkManager()
    {
        delete chunk;
    }

    void ChunkManager::Start()
    {
        chunkThread = std::thread(&ChunkManager::ChunkThreadUpdate, this);
    }

    void ChunkManager::Update()
    {
        playerChunkX = playerObj->position.x < 0 ? floor(playerObj->position.x / CHUNK_SIZE) : playerObj->position.x / CHUNK_SIZE;
        playerChunkY = playerObj->position.y < 0 ? floor(playerObj->position.y / CHUNK_SIZE) : playerObj->position.y / CHUNK_SIZE;
        playerChunkZ = playerObj->position.z < 0 ? floor(playerObj->position.z / CHUNK_SIZE) : playerObj->position.z / CHUNK_SIZE;
    }

    void ChunkManager::ChunkThreadUpdate()
    {
        while (!shouldEnd)
        {
            // Check if player moved to new chunk
            if (playerChunkX != lastPlayerX || playerChunkY != lastPlayerY || playerChunkZ != lastPlayerZ)
            {
                // Player moved chunks, start new chunk queue
                lastPlayerX = playerChunkX;
                lastPlayerY = playerChunkY;
                lastPlayerZ = playerChunkZ;

                chunkQueue = {};
                // Add current chunk
                chunkQueue.push({ playerChunkX, playerChunkY, playerChunkZ });

                for (int r = 0; r < renderDistance; r++)
                {
                    // Add middle chunks
                    for (int y = 0; y < renderHeight; y++)
                    {
                        chunkQueue.push({ playerChunkX,     playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ     });
                        chunkQueue.push({ playerChunkX,     playerChunkY + y, playerChunkZ - r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ     });

                        if (y > 0)
                        {
                            chunkQueue.push({ playerChunkX,     playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ     });
                            chunkQueue.push({ playerChunkX,     playerChunkY - y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ     });
                        }
                    }

                    // Add edges
                    for (int e = 1; e < r; e++)
                    {
                        for (int y = 0; y <= renderHeight; y++)
                        {
                            chunkQueue.push({ playerChunkX + e, playerChunkY + y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX - e, playerChunkY + y, playerChunkZ + r });

                            chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ + e });
                            chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ - e });

                            chunkQueue.push({ playerChunkX + e, playerChunkY + y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - e, playerChunkY + y, playerChunkZ - r });

                            chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ + e });
                            chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ - e });

                            if (y > 0)
                            {
                                chunkQueue.push({ playerChunkX + e, playerChunkY - y, playerChunkZ + r });
                                chunkQueue.push({ playerChunkX - e, playerChunkY - y, playerChunkZ + r });

                                chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ + e });
                                chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ - e });

                                chunkQueue.push({ playerChunkX + e, playerChunkY - y, playerChunkZ - r });
                                chunkQueue.push({ playerChunkX - e, playerChunkY - y, playerChunkZ - r });

                                chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ + e });
                                chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ - e });
                            }
                        }
                    }

                    // Add corners
                    for (int y = 0; y <= renderHeight; y++)
                    {
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX + r, playerChunkY + y, playerChunkZ - r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ + r });
                        chunkQueue.push({ playerChunkX - r, playerChunkY + y, playerChunkZ - r });

                        if (y > 0)
                        {
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX + r, playerChunkY - y, playerChunkZ - r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ + r });
                            chunkQueue.push({ playerChunkX - r, playerChunkY - y, playerChunkZ - r });
                        }
                    }
                }
            }
            else if (!chunkQueue.empty())
            {
                // Generate next chunk in queue
                glm::ivec3 chunkPos = chunkQueue.front();
                
                // If exists, skip
                chunkMutex.lock();
                if (chunks.find(chunkPos) != chunks.end())
                {
                    chunkMutex.unlock();
                    chunkQueue.pop();
                    continue;
                }
                chunkMutex.unlock();

                // Create chunk object
                Chunk* chunk = new Chunk(*terrainShader, chunkPos, chunkPos * CHUNK_SIZE);

                // Set chunk data
                {
                    chunkMutex.lock();
                    if (chunkData.find(chunkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->chunkData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[chunkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->chunkData = chunkData.at(chunkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set north chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z - 1);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->northData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->northData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set south chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z + 1);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->southData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->southData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set east chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x + 1, chunkPos.y, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->eastData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->eastData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set west chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x - 1, chunkPos.y, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->westData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->westData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set top chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y + 1, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->upData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->upData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Set down chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y - 1, chunkPos.z);
                    chunkMutex.lock();
                    if (chunkData.find(checkPos) == chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        chunkMutex.unlock();
                        uint16_t* d = new uint16_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
                        for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
                        {
                            //d[i] = std::rand() % 2;
                            d[i] = 1;
                        }
                        ChunkData* data = new ChunkData(d);

                        // Set chunk's chunk data
                        chunk->downData = data;

                        // Add new chunk data to chunk data map
                        chunkMutex.lock();
                        chunkData[checkPos] = data;
                        chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->downData = chunkData.at(checkPos);
                        chunkMutex.unlock();
                    }
                }

                // Generate chunk mesh
                chunk->GenerateChunkMeshData();

                // Add chunk to chunk map
                chunkMutex.lock();
                chunks[chunkPos] = chunk;
                chunkMutex.unlock();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    void ChunkManager::Render(Camera& camera)
    {
        glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix();
		terrainShader->Use();
		terrainShader->SetMat4("view", view);
		terrainShader->SetMat4("projection", projection);
        //chunk->Render();

        chunkMutex.lock();
        for (auto it = chunks.begin(); it != chunks.end();)
        {
            (*it->second).Render();
            ++it;
        }
        chunkMutex.unlock();
    }

    void ChunkManager::SetPlayerObj(Camera* camera)
    {
        playerObj = camera;
    }
}