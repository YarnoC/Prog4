#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>
#include "Font.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		//TODO: maybe change this to a concept for better errors
		template<typename ComponentType, typename... TArgs>
		void AddComponent(TArgs... tArgs)
		{
			//push back gets optimized so it's equally fast as emplace back
			m_ComponentVec.emplace_back(std::make_unique<ComponentType>(std::move(tArgs)...));
			//auto comp = m_ComponentVec.back();
			//comp.SetOwner(this);
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
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
	};
}
