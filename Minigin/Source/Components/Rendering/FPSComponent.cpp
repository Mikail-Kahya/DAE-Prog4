#include "FPSComponent.h"

#include "SceneManager.h"
#include "Texture2D.h"

using namespace mk;

void FPSComponent::Update()
{
	const TimeManager& time{ Time() };
	TextComponent::Update();
}

std::unique_ptr<Component> FPSComponent::Clone()
{
	return std::make_unique<FPSComponent>();
}
