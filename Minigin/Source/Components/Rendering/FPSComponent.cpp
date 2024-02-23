#include "FPSComponent.h"

#include "SceneManager.h"
#include "Texture2D.h"

using namespace mk;

void FPSComponent::Update()
{

	if (m_NeedsUpdate)
	{
		m_Timer -= m_UpdateDelay;
		UpdateText();
		TextComponent::Update();
		return;
	}

	m_Timer += Time().deltaTime;
	m_NeedsUpdate = m_Timer > m_UpdateDelay;
}

void FPSComponent::SetPrecision(int precision)
{
	m_Precision = precision;
}

void FPSComponent::SetUpdateDelay(float updateDelay)
{
	m_UpdateDelay = updateDelay;
}

std::unique_ptr<Component> FPSComponent::Clone()
{
	return std::make_unique<FPSComponent>();
}

void FPSComponent::UpdateText()
{
	std::stringstream textBuffer;
	textBuffer << std::fixed << std::setprecision(m_Precision) << Time().GetFPS();
	textBuffer << "  FPS";

	SetText(textBuffer.str());
}