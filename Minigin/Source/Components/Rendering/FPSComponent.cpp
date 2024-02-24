#include "FPSComponent.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "TextComponent.h"

using namespace mk;

FPSComponent::FPSComponent(GameObject* ownerPtr)
	: Component(ownerPtr)
{
	//m_TextCompPtr = ownerPtr->GetComponent<TextComponent>();
	//if (m_TextCompPtr == nullptr)
	//	m_TextCompPtr = ownerPtr->AddComponent<TextComponent>();

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