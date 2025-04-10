#pragma once
#include <vector>
#include "Event.h"

namespace dae
{
class Observer;
class Component;

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void NotifyObservers(Event event, Component* subject);

private:
	std::vector<Observer*> m_Observers{};

	virtual ~Subject() = default;
	Subject(const Subject&) = delete;
	Subject(Subject&&) = delete;
	Subject& operator=(const Subject&) = delete;
	Subject& operator=(Subject&&) = delete;
};

}

