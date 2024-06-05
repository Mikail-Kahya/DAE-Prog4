#include "HealthBarComponent.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Events/Events.h"

using namespace mk;

void HealthBarComponent::Start()
{
	IComponent::Start();

	m_TextCompPtr = GetOwner()->AddComponent<TextComponent>("Health: 0", "Lingua.otf", 30);
}

void HealthBarComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (PlayerDamageTakenEvent* damageEvent = dynamic_cast<PlayerDamageTakenEvent*>(event))
		m_TextCompPtr->SetText("Health: " + std::to_string(damageEvent->health));
}