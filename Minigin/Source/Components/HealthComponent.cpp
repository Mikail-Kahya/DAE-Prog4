#include "HealthComponent.h"

#include <algorithm>

#include "BoxColliderComponent.h"
#include "GameObject.h"

using namespace mk;

HealthComponent::HealthComponent(int maxHealth, int startHealth)
	: m_MaxHealth{ maxHealth }
	, m_Health{ startHealth }
{
}

void HealthComponent::Start()
{
	BoxColliderComponent* boxPtr{ GetOwner().GetComponent<BoxColliderComponent>() };
	if (boxPtr != nullptr)
		boxPtr->AddObserver(this);
	else
		assert(false && "No box component in healthComponent");
}

void HealthComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_OVERLAP)
		Hit();
}

void HealthComponent::Hit()
{
	m_Health = std::max(0, m_Health - 1);
	if (IsDead())
		GetOwner().Destroy();
}

bool HealthComponent::IsDead() const
{
	return m_Health <= 0;
}
