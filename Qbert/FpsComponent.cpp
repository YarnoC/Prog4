#include "FpsComponent.h"
#include "GameTime.h"
#include "GameObject.h"
#include "TextComponent.h"

#include <iostream>
#include <iomanip>
#include <sstream>

void FpsComponent::Update()
{
	const double fps = 1.0 / dae::GameTime::GetDt();
	
	//cache this, no getcomponent every frame in the hot code path
	//TextComponent* ptr = GetOwner()->GetComponent<TextComponent>();
	//if (ptr == nullptr)
	//{
	//	std::cerr << "No TextComponent found\n";
	//	return;
	//}

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << fps;

	m_TextComponentPtr->SetText(stream.str());
}

FpsComponent::FpsComponent(dae::GameObject* ownerPtr, dae::TextComponent* textComp)
	: Component(ownerPtr), m_TextComponentPtr{textComp}
{}
