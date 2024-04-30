#include "RespawnComponent.h"

#include "GameObject.h"

using namespace mk;

RespawnComponent::RespawnComponent(const glm::vec2& respawn)
	: m_Respawn{ respawn }
{
}

void RespawnComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_DIED)
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
