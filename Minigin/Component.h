#pragma once
#include "Transform.h"

namespace dae
{
class GameObject;
class Texture2D;
}

class Component
{
public:
    virtual ~Component() = default;

    virtual inline void Update() {};
    virtual inline void FixedUpdate() {};
    virtual dae::Texture2D* GetTexturePtr() const;

    dae::GameObject* GetOwner() const;

protected:
    dae::GameObject* m_OwnerPtr;
    bool m_IsTerminal{ false };
    

    Component(dae::GameObject* ownerPtr);

private:
};

