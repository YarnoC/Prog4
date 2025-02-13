#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "Font.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y);

		//TODO: maybe change this to a concept for better errors
		template<typename ComponentType, typename... TArgs>
		void AddComponent(TArgs... tArgs)
		{
			m_ComponentVec.emplace_back(std::make_unique<ComponentType>(this, std::move(tArgs)...));
		}

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::vector<std::unique_ptr<Component>> m_ComponentVec{};
	};
}
