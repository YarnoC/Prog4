#pragma once
#include "Component.h"

class Renderable : public Component
{
public:
	void virtual Render() const = 0;

protected:
	Renderable(dae::GameObject* ownerPtr) : Component(ownerPtr) {};

	~Renderable() = default;
	Renderable(const Renderable& other) = delete;
	Renderable(Renderable&& other) = delete;
	Renderable& operator=(const Renderable& other) = delete;
	Renderable&& operator=(Renderable&& other) = delete;
};