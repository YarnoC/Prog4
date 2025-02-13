#pragma once
#include "Component.h"

class Renderable : public Component
{
public:
	void virtual Render() const = 0;

protected:
	Renderable(dae::GameObject* ownerPtr) : Component(ownerPtr)
	{

	};
};