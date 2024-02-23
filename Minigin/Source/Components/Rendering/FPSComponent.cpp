#include <windows.h>

#include "FPSComponent.h"

#include "SceneManager.h"
#include "Texture2D.h"

using namespace mk;

void FPSComponent::Update()
{
	const TimeManager& time{ Time() };
	OutputDebugString(std::string{ "\nDT: " + std::to_string(time.deltaTime) + "\nFT: " + std::to_string(time.fixedDeltaTime) }.c_str());

	TextComponent::Update();
}

std::unique_ptr<Component> FPSComponent::Clone()
{
	return std::make_unique<FPSComponent>();
}
