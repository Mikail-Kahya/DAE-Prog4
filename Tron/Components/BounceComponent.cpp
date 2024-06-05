#include "BounceComponent.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "glm/detail/func_geometric.inl"

#include "MovementComponent.h"

using namespace mk;

void BounceComponent::Start()
{
	IComponent::Start();

	m_MoveCompPtr = GetOwner()->GetComponent<MovementComponent>();
}

void BounceComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (BlockEvent* blockEvent = dynamic_cast<BlockEvent*>(event))
		m_MoveCompPtr->SetDirection(glm::reflect(blockEvent->info.velocity, blockEvent->info.impactNormal));
}
