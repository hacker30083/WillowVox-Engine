#include <PlayerController.h>
#include <WillowVoxEngine/Application/Application.h>

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