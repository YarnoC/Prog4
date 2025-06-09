#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "Font.h"

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
		void LateUpdate();
		void Render();

		void SetPosition(float x, float y);

		template<IsComponentType ComponentType, typename... TArgs>
		ComponentType* AddComponent(TArgs... tArgs)
		{
			if (HasComponent<ComponentType>() == true) return nullptr; //only allow one (1) instance of a component type on a game object

			//credits to Matias Devred for showing me this way of returning the component immediately instead of this being a void function
			auto& newComp = m_ComponentVec.emplace_back(std::make_unique<ComponentType>(this, std::move(tArgs)...));

			return reinterpret_cast<ComponentType*>(newComp.get());
		}

		//TODO: make RemoveComponent
		//use std::erase_if for the remove func

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


		//schedules for destruction at the end of the late update
		void Destroy();
		bool IsTerminal() const;

		GameObject* GetParent() const;
		void SetParent(GameObject* parent, bool keepWorldPos);
		int GetChildCount() const;
		GameObject* GetChildAt(size_t index) const;
		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& newPos);
		glm::vec3 GetLocalPosition() const;
		void SetPositionDirty();

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<Component>> m_ComponentVec{};

		GameObject* m_ParentPtr = nullptr;
		std::vector<GameObject*> m_ChildrenVec;
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
		bool m_PositionIsDirty{ true };
		bool m_IsTerminal{ false };

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
	};
}
