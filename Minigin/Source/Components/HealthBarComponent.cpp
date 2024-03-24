#include "HealthBarComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

using namespace mk;

void HealthBarComponent::Start()
{
	Component::Start();

	m_TextCompPtr = GetOwner().AddComponent<TextComponent>("Health: 0", "Lingua.otf", 30);
}

void HealthBarComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::TAKE_DAMAGE)
	{
		int health{};
		if (event.GetData("health", health))
			m_TextCompPtr->SetText("Health: " + std::to_string(health));
	}
}
