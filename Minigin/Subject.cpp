#include "Subject.h"
#include "Observer.h"
#include "Component.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer); //maybe change to a reference
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(), [&](Observer* obs) {return obs == observer; }), m_Observers.end());
}

void dae::Subject::NotifyObservers(Event event, Component* subject)
{
	for (auto&& obs : m_Observers)
	{
		obs->Notify(event, subject);
	}
}
