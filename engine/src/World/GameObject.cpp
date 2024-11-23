#include <WillowVoxEngine/World/GameObject.h>

namespace WillowVox
{
    GameObject::~GameObject()
    {
        for (auto c : components)
        {
            delete c;
        }
    }

    void GameObject::Start()
    {
        for (auto c : components)
        {
            c->Start();
        }
    }

    void GameObject::Update()
    {
        for (auto c : components)
        {
            c->Update();
        }
    }

    void GameObject::AddComponent(Component* component)
    {
        components.push_back(component);
    }
}