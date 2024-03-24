#include "HealthComponent.h"

#include <algorithm>

using namespace mk;

HealthComponent::HealthComponent(int maxHealth, int startHealth)
	: m_MaxHealth{ maxHealth }
	, m_Health{ startHealth }
{
}

void HealthComponent::Hit()
{
	m_Health = std::max(0, m_Health - 1);
}

bool HealthComponent::IsDead() const
{
	return m_Health <= 0;
}
