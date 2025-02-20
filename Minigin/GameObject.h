#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "Font.h"
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;

	template<typename ComponentType>
	concept IsComponentType = requires(ComponentType) {
		{
			std::derived_from<ComponentType, Component>
		};
	};

	class GameObject final
	{
	public:
		void Update();
		void Render();

		void SetPosition(float x, float y);

		template<IsComponentType ComponentType, typename... TArgs>
		void AddComponent(TArgs... tArgs)
		{
			if (HasComponent<ComponentType>() == true) return; //only allow one (1) instance of a component type on a game object

			m_ComponentVec.emplace_back(std::make_unique<ComponentType>(this, std::move(tArgs)...));
		}

		//TODO: make RemoveComponent
		//use std::erase_if for the remove func

		dae::Transform GetTranform() const;

		template<IsComponentType ComponentType>
		ComponentType* GetComponent()
		{
			//didn't use find_if for this because i'd have to either dyn cast twice or ignore the it return val which causes a warning
			for (const auto& comp : m_ComponentVec)
			{
				ComponentType* compPtr = dynamic_cast<ComponentType*>(comp.get());

				if (compPtr != nullptr)
				{
					return compPtr;
				}
			}

			return nullptr;
		}
		
		template<IsComponentType ComponentType>
		bool HasComponent() const
		{
			return InternalGetComponent<ComponentType>() != nullptr;
		}

		GameObject* GetParent() const;
		void SetParent(GameObject* parent, bool keepWorldPos);
		int GetChildCount() const;
		GameObject* GetChildAt(size_t index) const;
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& newPos);
		void SetPositionDirty();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<Component>> m_ComponentVec{};

		GameObject* m_ParentPtr = nullptr;
		std::vector<GameObject*> m_ChildrenVec;
		Transform m_Transform{};
		bool m_PositionIsDirty{ true };
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};

		//functions

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		void UpdateWorldPosition();
		bool IsChild(GameObject* child) const;

		template<IsComponentType ComponentType>
		const Component* InternalGetComponent() const //DO NOT USE ANYWHERE EXCEPT IN IMPL OF HASCOMPONENT()
		{
			const auto& result = std::find_if(m_ComponentVec.begin(), m_ComponentVec.end(), [&](const std::unique_ptr<Component>& compUPtr)
				{
					return dynamic_cast<ComponentType*>(compUPtr.get()) != nullptr;
				});

			if (result == m_ComponentVec.end()) return nullptr;

			return result->get(); //returns Comp* which is not useful for actual operations but does not matter for this purpose
		}

		//cached components
		RenderComponent* m_RenderComponent;
	};
}
