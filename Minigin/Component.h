#pragma once
#include "Transform.h"

class GameObject;

class Component
{
public:
    virtual inline ~Component(){};

    virtual void Update() = 0;
    virtual void FixedUpdate() = 0;

    GameObject* GetOwner() const;

protected:
    GameObject* m_OwnerPtr;
    bool m_IsTerminal{ false };

    Component() = default;

private:
};

