#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"

#include <functional>

dae::Transform dae::GameObject::GetTranform() const
{
	return m_Transform;
}

bool dae::GameObject::IsTerminal() const
{
	return m_IsTerminal;
}

void dae::GameObject::Destroy()
{
	m_IsTerminal = true;

	//schedule destroy for all children in scenegraph
	for (const auto& child : m_ChildrenVec)
	{
		child->Destroy();
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_ParentPtr;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPos)
{
	if (IsChild(parent) or parent == this or m_ParentPtr == parent) return;

	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPos)
		{
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		}
		SetPositionDirty();
	}

	if (m_ParentPtr)
	{
		m_ParentPtr->RemoveChild(this);
	}

	m_ParentPtr = parent;

	if (m_ParentPtr)
	{
		m_ParentPtr->AddChild(this);
	}
}

int dae::GameObject::GetChildCount() const
{
	return 0;
}

dae::GameObject* dae::GameObject::GetChildAt(size_t index) const
{
	if (index < 0 or index >= m_ChildrenVec.size()) return nullptr;

	return m_ChildrenVec[index];
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& newPos)
{
	m_LocalPosition = newPos;
	SetPositionDirty();
}

glm::vec3 dae::GameObject::GetLocalPosition() const
{
	return m_LocalPosition;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	std::for_each(m_ChildrenVec.begin(), m_ChildrenVec.end(), std::mem_fn(&dae::GameObject::SetPositionDirty));
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_ChildrenVec.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	auto it = std::find_if(m_ChildrenVec.begin(), m_ChildrenVec.end(), [&](const auto& ownedChild)
		{
			return ownedChild == child;
		});

	if (it == m_ChildrenVec.end()) return;

	m_ChildrenVec.erase(it); //doesn't matter if it invalidates iterators because only doing 1 item at a time
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_ParentPtr == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = m_ParentPtr->GetWorldPosition() + m_LocalPosition;
		}
	}
	m_PositionIsDirty = false;
}

bool dae::GameObject::IsChild(GameObject* object) const
{
	for (const auto& child : m_ChildrenVec)
	{
		if (child == object)
		{
			return true;
		}

		if (child->IsChild(object))
		{
			return true;
		}
	}
	return false;
}

void dae::GameObject::Update()
{
	for (auto&& comp : m_ComponentVec)
	{
		comp->Update();
	}
}

void dae::GameObject::LateUpdate()
{

	//destroy any terminal components
	std::erase_if(m_ComponentVec, [](std::unique_ptr<Component>& comp)
		{
			return comp->IsTerminal();
		});
}

//TODO: make awake so this can be const again
void dae::GameObject::Render()
{
	//should maybe make an awake so i can do the stuff there
	if (m_RenderComponent == nullptr)
	{
		m_RenderComponent = GetComponent<RenderComponent>();
	}

	if (m_RenderComponent == nullptr) return;

	m_RenderComponent->Render();
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
