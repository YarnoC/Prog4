#pragma once
#include "Transform.h"

namespace dae
{
class GameObject;
}

class Component
{
public:
    virtual ~Component() = default;

    virtual inline void Update() {};
    virtual inline void FixedUpdate() {};

    dae::GameObject* GetOwner() const;
    void SetOwner(dae::GameObject* ownerPtr);

protected:
    dae::GameObject* m_OwnerPtr;
    bool m_IsTerminal{ false };

    Component() = default;

private:
};

