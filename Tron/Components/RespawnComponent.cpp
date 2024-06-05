#include "RespawnComponent.h"

#include "GameObject.h"
#include "Events/Events.h"

using namespace mk;

RespawnComponent::RespawnComponent(const glm::vec2& respawn)
	: m_Respawn{ respawn }
{
}

void RespawnComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (dynamic_cast<PlayerDiedEvent*>(event))
		Respawn();
}

void RespawnComponent::SetRespawn(const glm::vec2& respawn)
{
	m_Respawn = respawn;
}

void RespawnComponent::Respawn() const
{
	GetOwner()->SetLocalPosition(m_Respawn);
}
