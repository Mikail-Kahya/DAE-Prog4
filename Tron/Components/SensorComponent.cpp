#include "SensorComponent.h"

using namespace mk;

void SensorComponent::OnNotify(ISubject* subjectPtr, const Event& event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_BLOCK)
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
