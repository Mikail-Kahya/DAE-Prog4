#include <windows.h>

#include "FPSComponent.h"

#include "SceneManager.h"
#include "Texture2D.h"

using namespace mk;

void FPSComponent::Update()
{
	const TimeManager& time{ Time() };

	std::stringstream textBuffer;
	textBuffer << std::fixed << std::setprecision(2) << time.GetFPS();

	SetText(textBuffer.str());

	TextComponent::Update();
}

std::unique_ptr<Component> FPSComponent::Clone()
{
	return std::make_unique<FPSComponent>();
}
