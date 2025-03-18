#include <WillowVox/world/ChunkManager.h>
#include <WillowVox/world/WorldGlobals.h>
#include <WillowVox/core/Logger.h>

namespace WillowVox
{

    ChunkManager::~ChunkManager()
    {

    }

    void ChunkManager::Start()
    {
        _chunkThread = std::thread(&ChunkManager::ChunkThreadUpdate, this);
    }

    void ChunkManager::Update()
    {
        _playerChunkX = _playerObj->position.x < 0 ? floor(_playerObj->position.x / CHUNK_SIZE) : _playerObj->position.x / CHUNK_SIZE;
        _playerChunkY = _playerObj->position.y < 0 ? floor(_playerObj->position.y / CHUNK_SIZE) : _playerObj->position.y / CHUNK_SIZE;
        _playerChunkZ = _playerObj->position.z < 0 ? floor(_playerObj->position.z / CHUNK_SIZE) : _playerObj->position.z / CHUNK_SIZE;
    }

    void ChunkManager::ChunkThreadUpdate()
    {
        while (!_shouldEnd)
        {
            // Delete unused chunk data
            for (auto it = _chunkData.begin(); it != _chunkData.end(); )
            {
                glm::ivec3 pos = it->first;

                if (_chunks.find(pos) == _chunks.end() &&
                    _chunks.find({ pos.x + 1, pos.y, pos.z }) == _chunks.end() &&
                    _chunks.find({ pos.x - 1, pos.y, pos.z }) == _chunks.end() &&
                    _chunks.find({ pos.x, pos.y + 1, pos.z }) == _chunks.end() &&
                    _chunks.find({ pos.x, pos.y - 1, pos.z }) == _chunks.end() &&
                    _chunks.find({ pos.x, pos.y, pos.z + 1 }) == _chunks.end() &&
                    _chunks.find({ pos.x, pos.y, pos.z - 1 }) == _chunks.end())
                {
                    delete it->second;
                    it = _chunkData.erase(it);
                }
                else
                    ++it;
            }

            // Check if player moved to new chunk or if the chunk queue should be cleared
            if (_playerChunkX != _lastPlayerX || _playerChunkY != _lastPlayerY || _playerChunkZ != _lastPlayerZ || _shouldClearChunkQueue)
            {
                // Player moved chunks, start new chunk queue
                _lastPlayerX = _playerChunkX;
                _lastPlayerY = _playerChunkY;
                _lastPlayerZ = _playerChunkZ;

                _shouldClearChunkQueue = false;

                _chunkQueue = {};

                // Add current chunk
                _chunkQueue.push({ _playerChunkX, _playerChunkY, _playerChunkZ });

                for (int r = 0; r < m_renderDistance; r++)
                {
                    // Add middle chunks
                    for (int y = 0; y < m_renderHeight; y++)
                    {
                        _chunkQueue.push({ _playerChunkX,     _playerChunkY + y, _playerChunkZ + r });
                        _chunkQueue.push({ _playerChunkX + r, _playerChunkY + y, _playerChunkZ });
                        _chunkQueue.push({ _playerChunkX,     _playerChunkY + y, _playerChunkZ - r });
                        _chunkQueue.push({ _playerChunkX - r, _playerChunkY + y, _playerChunkZ });

                        if (y > 0)
                        {
                            _chunkQueue.push({ _playerChunkX,     _playerChunkY - y, _playerChunkZ + r });
                            _chunkQueue.push({ _playerChunkX + r, _playerChunkY - y, _playerChunkZ });
                            _chunkQueue.push({ _playerChunkX,     _playerChunkY - y, _playerChunkZ - r });
                            _chunkQueue.push({ _playerChunkX - r, _playerChunkY - y, _playerChunkZ });
                        }
                    }

                    // Add edges
                    for (int e = 1; e < r; e++)
                    {
                        for (int y = 0; y <= m_renderHeight; y++)
                        {
                            _chunkQueue.push({ _playerChunkX + e, _playerChunkY + y, _playerChunkZ + r });
                            _chunkQueue.push({ _playerChunkX - e, _playerChunkY + y, _playerChunkZ + r });
                            
                            _chunkQueue.push({ _playerChunkX + r, _playerChunkY + y, _playerChunkZ + e });
                            _chunkQueue.push({ _playerChunkX + r, _playerChunkY + y, _playerChunkZ - e });
                            
                            _chunkQueue.push({ _playerChunkX + e, _playerChunkY + y, _playerChunkZ - r });
                            _chunkQueue.push({ _playerChunkX - e, _playerChunkY + y, _playerChunkZ - r });
                            
                            _chunkQueue.push({ _playerChunkX - r, _playerChunkY + y, _playerChunkZ + e });
                            _chunkQueue.push({ _playerChunkX - r, _playerChunkY + y, _playerChunkZ - e });

                            if (y > 0)
                            {
                                _chunkQueue.push({ _playerChunkX + e, _playerChunkY - y, _playerChunkZ + r });
                                _chunkQueue.push({ _playerChunkX - e, _playerChunkY - y, _playerChunkZ + r });
                                
                                _chunkQueue.push({ _playerChunkX + r, _playerChunkY - y, _playerChunkZ + e });
                                _chunkQueue.push({ _playerChunkX + r, _playerChunkY - y, _playerChunkZ - e });
                                
                                _chunkQueue.push({ _playerChunkX + e, _playerChunkY - y, _playerChunkZ - r });
                                _chunkQueue.push({ _playerChunkX - e, _playerChunkY - y, _playerChunkZ - r });
                                
                                _chunkQueue.push({ _playerChunkX - r, _playerChunkY - y, _playerChunkZ + e });
                                _chunkQueue.push({ _playerChunkX - r, _playerChunkY - y, _playerChunkZ - e });
                            }
                        }
                    }

                    // Add corners
                    for (int y = 0; y <= m_renderHeight; y++)
                    {
                        _chunkQueue.push({ _playerChunkX + r, _playerChunkY + y, _playerChunkZ + r });
                        _chunkQueue.push({ _playerChunkX + r, _playerChunkY + y, _playerChunkZ - r });
                        _chunkQueue.push({ _playerChunkX - r, _playerChunkY + y, _playerChunkZ + r });
                        _chunkQueue.push({ _playerChunkX - r, _playerChunkY + y, _playerChunkZ - r });

                        if (y > 0)
                        {
                            _chunkQueue.push({ _playerChunkX + r, _playerChunkY - y, _playerChunkZ + r });
                            _chunkQueue.push({ _playerChunkX + r, _playerChunkY - y, _playerChunkZ - r });
                            _chunkQueue.push({ _playerChunkX - r, _playerChunkY - y, _playerChunkZ + r });
                            _chunkQueue.push({ _playerChunkX - r, _playerChunkY - y, _playerChunkZ - r });
                        }
                    }
                }
            }
            else if (!_chunkQueue.empty())
            {
                // Generate next chunk in queue
                glm::ivec3 chunkPos = _chunkQueue.front();

                // If exists, skip
                _chunkMutex.lock();
                if (_chunks.find(chunkPos) != _chunks.end())
                {
                    _chunkMutex.unlock();
                    _chunkQueue.pop();
                    continue;
                }
                _chunkMutex.unlock();

                // Create chunk object
                Chunk* chunk = new Chunk(*this, m_solidMaterial, m_fluidMaterial, m_billboardMaterial, chunkPos, chunkPos * CHUNK_SIZE);

                // Set chunk data
                {
                    _chunkMutex.lock();
                    if (_chunkData.find(chunkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = chunkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_chunkData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[chunkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_chunkData = _chunkData.at(chunkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set north chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z - 1);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_northData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_northData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set south chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y, chunkPos.z + 1);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_southData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_southData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set east chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x + 1, chunkPos.y, chunkPos.z);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_eastData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_eastData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set west chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x - 1, chunkPos.y, chunkPos.z);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_westData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_westData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set top chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y + 1, chunkPos.z);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_upData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_upData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Set down chunk data
                {
                    glm::ivec3 checkPos(chunkPos.x, chunkPos.y - 1, chunkPos.z);
                    _chunkMutex.lock();
                    if (_chunkData.find(checkPos) == _chunkData.end())
                    {
                        // Chunk data doesn't exist, create it
                        _chunkMutex.unlock();

                        ChunkData* data = new ChunkData();
                        data->m_offset = checkPos * CHUNK_SIZE;
                        _worldGen.GenerateChunkData(*data);

                        // Set chunk's chunk data
                        chunk->m_downData = data;

                        // Add new chunk data to chunk data map
                        _chunkMutex.lock();
                        _chunkData[checkPos] = data;
                        _chunkMutex.unlock();
                    }
                    else
                    {
                        // Set chunk's data to item from chunk data map
                        chunk->m_downData = _chunkData.at(checkPos);
                        _chunkMutex.unlock();
                    }
                }

                // Generate chunk mesh
                chunk->GenerateChunkMeshData();

                // Add chunk to chunk map
                _chunkMutex.lock();
                _chunks[chunkPos] = chunk;
                _chunkMutex.unlock();
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

        m_solidMaterial->Bind();
        m_solidMaterial->SetCameraShaderProperties(view, projection);

        m_fluidMaterial->Bind();
        m_fluidMaterial->SetCameraShaderProperties(view, projection);

        m_billboardMaterial->Bind();
        m_billboardMaterial->SetCameraShaderProperties(view, projection);

        _chunkMutex.lock();
        int numChunks = 0;
        for (auto it = _chunks.begin(); it != _chunks.end();)
        {
            Chunk& chunk = *it->second;

            int chunkX = chunk.m_chunkPos.x;
            int chunkY = chunk.m_chunkPos.y;
            int chunkZ = chunk.m_chunkPos.z;
            if (abs(chunkX - _playerChunkX) > m_renderDistance ||
                abs(chunkY - _playerChunkY) > m_renderDistance ||
                abs(chunkZ - _playerChunkZ) > m_renderDistance)
            {
                delete it->second;
                it = _chunks.erase(it);
            }
            else
            {
                numChunks++;
                chunk.RenderSolid(view, projection);
                ++it;
            }
        }
        for (auto it = _chunks.begin(); it != _chunks.end();)
        {
            (*it->second).RenderTransparent();
            ++it;
        }
        //Logger::EngineLog("%d chunks rendered", numChunks);
        _chunkMutex.unlock();
    }

    Chunk* ChunkManager::GetChunk(int x, int y, int z)
    {
        _chunkMutex.lock();
        Chunk* c;
        if (_chunks.find(glm::ivec3(x, y, z)) == _chunks.end())
            c = nullptr;
        else
            c = _chunks.at(glm::ivec3(x, y, z));

        _chunkMutex.unlock();
        return c;
    }

    Chunk* ChunkManager::GetChunk(glm::ivec3 pos)
    {
        _chunkMutex.lock();
        Chunk* c;
        if (_chunks.find(pos) == _chunks.end())
            c = nullptr;
        else
            c = _chunks.at(pos);

        _chunkMutex.unlock();
        return c;
    }


    Chunk* ChunkManager::GetChunkAtPos(float x, float y, float z)
    {
        int cX = x < 0 ? floor(x / CHUNK_SIZE) : x / CHUNK_SIZE;
        int cY = y < 0 ? floor(y / CHUNK_SIZE) : y / CHUNK_SIZE;
        int cZ = z < 0 ? floor(z / CHUNK_SIZE) : z / CHUNK_SIZE;

        _chunkMutex.lock();
        Chunk* c;
        if (_chunks.find(glm::ivec3(cX, cY, cZ)) == _chunks.end())
            c = nullptr;
        else
            c = _chunks.at(glm::ivec3(cX, cY, cZ));

        _chunkMutex.unlock();
        return c;
    }

    Chunk* ChunkManager::GetChunkAtPos(glm::vec3 pos)
    {
        int cX = pos.x < 0 ? floor(pos.x / CHUNK_SIZE) : pos.x / CHUNK_SIZE;
        int cY = pos.y < 0 ? floor(pos.y / CHUNK_SIZE) : pos.y / CHUNK_SIZE;
        int cZ = pos.z < 0 ? floor(pos.z / CHUNK_SIZE) : pos.z / CHUNK_SIZE;

        _chunkMutex.lock();
        Chunk* c;
        if (_chunks.find(glm::ivec3(cX, cY, cZ)) == _chunks.end())
            c = nullptr;
        else
            c = _chunks.at(glm::ivec3(cX, cY, cZ));

        _chunkMutex.unlock();
        return c;
    }

    uint16_t ChunkManager::GetBlockIdAtPos(float x, float y, float z)
    {
        int blockX = x < 0 ? x - 1 : x;
        int blockY = y < 0 ? y - 1 : y;
        int blockZ = z < 0 ? z - 1 : z;

        int chunkX = blockX < 0 ? floorf(blockX / (float)CHUNK_SIZE) : blockX / (int)CHUNK_SIZE;
        int chunkY = blockY < 0 ? floorf(blockY / (float)CHUNK_SIZE) : blockY / (int)CHUNK_SIZE;
        int chunkZ = blockZ < 0 ? floorf(blockZ / (float)CHUNK_SIZE) : blockZ / (int)CHUNK_SIZE;

        int localBlockX = blockX - (chunkX * CHUNK_SIZE);
        int localBlockY = blockY - (chunkY * CHUNK_SIZE);
        int localBlockZ = blockZ - (chunkZ * CHUNK_SIZE);

        Chunk* chunk = GetChunk(chunkX, chunkY, chunkZ);
        if (chunk != nullptr)
            return chunk->GetBlockIdAtPos(localBlockX, localBlockY, localBlockZ);

        return 0;
    }

    uint16_t ChunkManager::GetBlockIdAtPos(glm::vec3 pos)
    {
        int blockX = pos.x < 0 ? pos.x - 1 : pos.x;
        int blockY = pos.y < 0 ? pos.y - 1 : pos.y;
        int blockZ = pos.z < 0 ? pos.z - 1 : pos.z;

        int chunkX = blockX < 0 ? floorf(blockX / (float)CHUNK_SIZE) : blockX / (int)CHUNK_SIZE;
        int chunkY = blockY < 0 ? floorf(blockY / (float)CHUNK_SIZE) : blockY / (int)CHUNK_SIZE;
        int chunkZ = blockZ < 0 ? floorf(blockZ / (float)CHUNK_SIZE) : blockZ / (int)CHUNK_SIZE;

        int localBlockX = blockX - (chunkX * CHUNK_SIZE);
        int localBlockY = blockY - (chunkY * CHUNK_SIZE);
        int localBlockZ = blockZ - (chunkZ * CHUNK_SIZE);

        Chunk* chunk = GetChunk(chunkX, chunkY, chunkZ);
        if (chunk != nullptr)
            return chunk->GetBlockIdAtPos(localBlockX, localBlockY, localBlockZ);

        return 0;
    }

    void ChunkManager::ClearChunkQueue()
    {
        _shouldClearChunkQueue = true;
    }

    void ChunkManager::SetPlayerObj(Camera* camera)
    {
        _playerObj = camera;
    }
}