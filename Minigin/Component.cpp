#include "Component.h"
#include "GameObject.h"

dae::GameObject* Component::GetOwner() const
{
    return m_OwnerPtr;
}

void Component::SetOwner(dae::GameObject* ownerPtr)
{
    m_OwnerPtr = ownerPtr;
}
