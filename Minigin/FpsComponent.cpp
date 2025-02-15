#include "FpsComponent.h"
#include "GameTime.h"
#include "GameObject.h"
#include "TextComponent.h"

#include <iostream>
#include <iomanip>
#include <sstream>

void FpsComponent::Update()
{
	const double fps = 1.0 / GAMETIME::GetDt();
	
	TextComponent* ptr = m_OwnerPtr->GetComponent<TextComponent>();
	if (ptr == nullptr)
	{
		std::cerr << "No TextComponent found\n";
		return;
	}

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << fps;

	ptr->SetText(stream.str());
}

FpsComponent::FpsComponent(dae::GameObject* ownerPtr) : Component(ownerPtr)
{}
