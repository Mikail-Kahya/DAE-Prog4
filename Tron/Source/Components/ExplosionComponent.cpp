#include "ExplosionComponent.h"

#include "GameObject.h"

using namespace mk;

void ExplosionComponent::OnNotify(ISubject* subjectPtr, const Event& event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (event.type == EventType::OBJECT_OVERLAP)
		GetOwner()->Destroy();
}
