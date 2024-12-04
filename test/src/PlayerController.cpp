#include <PlayerController.h>
#include <WillowVoxEngine/Application/Application.h>
#include <WillowVoxEngine/Physics/Physics.h>
#include <WillowVoxEngine/World/Chunk.h>
#include <WillowVoxEngine/World/ChunkManager.h>
#include <WillowVoxEngine/Resources/Block.h>
#include <WillowVoxEngine/Resources/Blocks.h>

void PlayerController::Start()
{
    WillowVox::Application::app->input->DisableMouse();
    WillowVox::Application::app->input->keyPressEventDispatcher.RegisterListener([this](WillowVox::KeyPressEvent& e) {
        if (e.key == WillowVox::ESC)
        {
            this->mouseLocked = !this->mouseLocked;
            if (this->mouseLocked)
                WillowVox::Application::app->input->DisableMouse();
            else
                WillowVox::Application::app->input->EnableMouse();
        }
    });

    WillowVox::Application::app->input->mouseMoveEventDispatcher.RegisterListener([this](WillowVox::MouseMoveEvent& e) {
        if (!this->mouseLocked)
            return;
        
        if (this->firstMouseMovement)
        {
            this->firstMouseMovement = false;
            return;
        }

        float xoffset = e.xOffset * this->mouseSensitivity;
        float yoffset = e.yOffset * this->mouseSensitivity;

        camera->direction.y += xoffset;
        camera->direction.x += yoffset;

        if (camera->direction.x > 89.0f)
            camera->direction.x = 89.0f;
        if (camera->direction.x < -89.0f)
            camera->direction.x = -89.0f;
    });

    WillowVox::Application::app->input->mouseScrollEventDispatcher.RegisterListener([this](WillowVox::MouseScrollEvent& e) {
        this->movementSpeed += (float)e.yOffset;
        if (this->movementSpeed < 0)
            this->movementSpeed = 0;
    });

    WillowVox::Application::app->input->mouseClickEventDispatcher.RegisterListener([this](WillowVox::MouseClickEvent& e) {
        auto result = WillowVox::Physics::Raycast(this->camera->position, this->camera->Front(), 10.0f);
        if (!result.hit)
            return;

        if (e.button == 0)
        {
            result.chunk->SetBlock(result.localBlockX, result.localBlockY, result.localBlockZ, 0);
        }
        else if (e.button == 1)
        {
            float distX = result.hitPos.x - (result.blockX + .5f);
            float distY = result.hitPos.y - (result.blockY + .5f);
            float distZ = result.hitPos.z - (result.blockZ + .5f);

            int blockX = result.blockX;
            int blockY = result.blockY;
            int blockZ = result.blockZ;
            
            // Choose face to place on
            if (abs(distX) > abs(distY) && abs(distX) > abs(distZ))
                blockX += (distX > 0 ? 1 : -1);
            else if (abs(distY) > abs(distX) && abs(distY) > abs(distZ))
                blockY += (distY > 0 ? 1 : -1);
            else
                blockZ += (distZ > 0 ? 1 : -1);

            int chunkX = blockX < 0 ? floorf(blockX / (float)CHUNK_SIZE) : blockX / (int)CHUNK_SIZE;
            int chunkY = blockY < 0 ? floorf(blockY / (float)CHUNK_SIZE) : blockY / (int)CHUNK_SIZE;
            int chunkZ = blockZ < 0 ? floorf(blockZ / (float)CHUNK_SIZE) : blockZ / (int)CHUNK_SIZE;

            int localBlockX = blockX - (chunkX * CHUNK_SIZE);
            int localBlockY = blockY - (chunkY * CHUNK_SIZE);
            int localBlockZ = blockZ - (chunkZ * CHUNK_SIZE);

            auto chunk = WillowVox::ChunkManager::instance->GetChunk(chunkX, chunkY, chunkZ);
            if (chunk == nullptr)
                return;
            
            uint16_t blockToReplace = chunk->GetBlockIdAtPos(localBlockX, localBlockY, localBlockZ);
            if (blockToReplace == 0 || WillowVox::Blocks::GetBlock(blockToReplace).blockType == WillowVox::Block::LIQUID)
                chunk->SetBlock(localBlockX, localBlockY, localBlockZ, 1);
            }
    });
}


void PlayerController::Update()
{
    float velocity = movementSpeed * WillowVox::Application::app->deltaTime;

    if (WillowVox::Application::app->input->GetKey(WillowVox::W))
    {
        if (WillowVox::Application::app->input->GetKey(WillowVox::SPACE))
        {
            glm::vec3 moveDir = camera->Front();
            moveDir.y = 0;
            moveDir = glm::normalize(moveDir);
            camera->position += moveDir * velocity;
        }
        else
            camera->position += camera->Front() * velocity;
    }
    if (WillowVox::Application::app->input->GetKey(WillowVox::S))
    {
        if (WillowVox::Application::app->input->GetKey(WillowVox::SPACE))
        {
            glm::vec3 moveDir = camera->Front();
            moveDir.y = 0;
            moveDir = glm::normalize(moveDir);
            camera->position -= moveDir * velocity;
        }
        else
            camera->position -= camera->Front() * velocity;
    }
    if (WillowVox::Application::app->input->GetKey(WillowVox::A))
        camera->position -= camera->Right() * velocity;
    if (WillowVox::Application::app->input->GetKey(WillowVox::D))
        camera->position += camera->Right() * velocity;
    if (WillowVox::Application::app->input->GetKey(WillowVox::E))
        camera->position += (absoluteVerticalMovement ? glm::vec3(0, 1, 0) : camera->Up()) * velocity;
    if (WillowVox::Application::app->input->GetKey(WillowVox::Q))
        camera->position -= (absoluteVerticalMovement ? glm::vec3(0, 1, 0) : camera->Up()) * velocity;
}