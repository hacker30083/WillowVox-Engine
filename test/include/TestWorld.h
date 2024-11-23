#pragma once

#include <WillowVoxEngine/WillowVox.h>

class TestWorld : public WillowVox::World
{
public:
    TestWorld()
    {
        WillowVox::GameObject* player = new WillowVox::GameObject();
        mainCamera = new WillowVox::Camera();
        player->AddComponent(mainCamera);
        AddGameObject(player);
    }
};