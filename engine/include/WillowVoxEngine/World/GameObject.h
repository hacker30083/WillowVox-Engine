#pragma once

#include <WillowVoxEngine/World/Component.h>
#include <vector>

namespace WillowVox
{
    class GameObject
    {
    public:
        ~GameObject();

        void Start();
        void Update();

        void AddComponent(Component* component);

    private:
        std::vector<Component*> components;
    };
}