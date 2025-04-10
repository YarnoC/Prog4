#include "Component.h"
#include "GameObject.h"

void dae::Component::Destroy()
{
    m_IsTerminal = true;
}

bool dae::Component::IsTerminal()
{
    return m_IsTerminal;
}

dae::GameObject* dae::Component::GetOwner() const
{
    return m_OwnerPtr;
}

dae::Component::Component(dae::GameObject* ownerPtr) : m_OwnerPtr{ ownerPtr }
{
}
