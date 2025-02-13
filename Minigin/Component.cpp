#include "Component.h"
#include "GameObject.h"

dae::GameObject* Component::GetOwner() const
{
    return m_OwnerPtr;
}

Component::Component(dae::GameObject* ownerPtr) : m_OwnerPtr{ ownerPtr }
{
}
