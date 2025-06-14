#pragma once
#include <vector>
#include "Event.h"

namespace dae
{
class Observer;
class Component;

class Subject final
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

	void NotifyObservers(Event event, Component* subject);

	Subject() = default;

	virtual ~Subject() = default;
	Subject(const Subject&) = delete;
	Subject(Subject&&) = delete;
	Subject& operator=(const Subject&) = delete;
	Subject& operator=(Subject&&) = delete;

private:
	std::vector<Observer*> m_Observers{};
};

}

