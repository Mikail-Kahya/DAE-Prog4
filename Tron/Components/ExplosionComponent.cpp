#include "ExplosionComponent.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"

using namespace mk;

void ExplosionComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (dynamic_cast<OverlapEvent*>(event))
		GetOwner()->Destroy();
}