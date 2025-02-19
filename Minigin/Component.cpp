#include "Component.h"
#include "GameObject.h"

dae::GameObject* Component::GetOwner() const
{
    return m_OwnerPtr;
}

//returns Texture2D* if the func is overriden in any class that needs to be rendered, else returns nullptr
dae::Texture2D* Component::GetTexturePtr() const
{
    return nullptr;
}

Component::Component(dae::GameObject* ownerPtr) : m_OwnerPtr{ ownerPtr }
{
}
