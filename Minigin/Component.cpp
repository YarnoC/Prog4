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

//returns Texture2D* if the func is overriden in any class that needs to be rendered, else returns nullptr
dae::Texture2D* dae::Component::GetTexturePtr() const
{
    return nullptr;
}

dae::Component::Component(dae::GameObject* ownerPtr) : m_OwnerPtr{ ownerPtr }
{
}
