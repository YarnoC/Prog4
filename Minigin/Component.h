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
    virtual inline void Render() const {};
    virtual dae::Texture2D* GetTexturePtr() const;

    //marks as terminal and will be destroyed at and of late update
    void Destroy();
    bool IsTerminal();

    dae::GameObject* GetOwner() const;

protected:
    bool m_IsTerminal{ false };
    

    Component(dae::GameObject* ownerPtr);

private:
    dae::GameObject* m_OwnerPtr;
};

