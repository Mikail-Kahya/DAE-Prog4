#include "DeathComponent.h"

#include "GameObject.h"
#include "Events/Events.h"

void mk::DeathComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (dynamic_cast<ObjectDiedEvent*>(event))
		GetOwner()->Destroy();
		
}
