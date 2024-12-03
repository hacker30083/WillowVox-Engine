#pragma once

namespace WillowVox
{
    class Component
    {
    public:
        virtual ~Component() = default;

        virtual void Start() {}
        virtual void Update() {}
    };
}