#pragma once
#include "Event.h"

namespace dae
{

class Component;

class Observer
{
public:
	virtual void Notify(const Event& event, Component* subject) = 0;
	virtual ~Observer() = default;

	Observer(const Observer&) = delete;
	Observer(Observer&&) = delete;
	Observer& operator=(const Observer&) = delete;
	Observer& operator=(Observer&&) = delete;
};

}