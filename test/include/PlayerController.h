#pragma once

#include <WillowVoxEngine/Core/Logger.h>
#include <WillowVoxEngine/World/Component.h>
#include <WillowVoxEngine/Rendering/Camera.h>

class PlayerController : public WillowVox::Component
{
public:
    PlayerController(WillowVox::Camera* camera) : camera(camera) {}

    void PlayerController::Start() override;
    void PlayerController::Update() override;

private:
    WillowVox::Camera* camera;
    float movementSpeed = 5.0f;
    float mouseSensitivity = .1f;
    bool mouseLocked = true;
    bool absoluteVerticalMovement = false;
    bool firstMouseMovement = true;
};