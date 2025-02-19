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
		void Render() const;

		void SetPosition(float x, float y);

		template<IsComponentType ComponentType, typename... TArgs>
		void AddComponent(TArgs... tArgs)
		{
			m_ComponentVec.emplace_back(std::make_unique<ComponentType>(this, std::move(tArgs)...));
		}

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

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform{};
		std::vector<std::unique_ptr<Component>> m_ComponentVec{};

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
