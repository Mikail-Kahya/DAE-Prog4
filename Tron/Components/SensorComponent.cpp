#include "SensorComponent.h"

#include "BoxColliderComponent.h"

using namespace mk;

void SensorComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (dynamic_cast<BlockEvent*>(event))
		m_HitWall = true;
}

void SensorComponent::FixedUpdate()
{
	IComponent::FixedUpdate();
	m_HitWall = false;
}

bool SensorComponent::HitWall() const
{
	return m_HitWall;
}
