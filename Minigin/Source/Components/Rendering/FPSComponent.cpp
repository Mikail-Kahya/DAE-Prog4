#include "FPSComponent.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "Texture2D.h"

using namespace mk;

FPSComponent::FPSComponent(GameObject* ownerPtr)
	: Component(ownerPtr)
{
	m_TextCompPtr = ownerPtr->AddComponent<TextComponent>();
	m_TextCompPtr->SetFont("Lingua.otf", 36);
	m_TextCompPtr->SetPosition(0, 20);
}

void FPSComponent::Update()
{
	if (m_TextCompPtr == nullptr)
		return;

	if (m_NeedsUpdate)
	{
		m_Timer -= m_UpdateDelay;

		// Update text component
		std::stringstream textBuffer;
		textBuffer << std::fixed << std::setprecision(m_Precision) << Time().GetFPS();
		textBuffer << "  FPS";

		m_TextCompPtr->SetText(textBuffer.str());

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