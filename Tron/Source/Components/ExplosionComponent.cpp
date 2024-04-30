#include "ExplosionComponent.h"

#include "GameObject.h"

using namespace mk;

void ExplosionComponent::OnNotify(Subject* subjectPtr, const Event& event)
{
	Observer::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_OVERLAP)
		GetOwner()->Destroy();
}
