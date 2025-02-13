#pragma once
#include "Transform.h"

namespace dae
{
class GameObject;
}

class Component
{
public:
    virtual inline ~Component(){};

    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;

    dae::GameObject* GetOwner() const;
    void SetOwner(dae::GameObject* ownerPtr);

protected:
    dae::GameObject* m_OwnerPtr;
    bool m_IsTerminal{ false };

    Component() = default;

private:
};

