#include "BounceComponent.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"

#include "MovementComponent.h"
#include "SceneManager.h"

using namespace mk;

BounceComponent::BounceComponent(int maxNrBounces)
	: m_MaxNrBounces{ maxNrBounces }
{
}

void BounceComponent::Start()
{
	IComponent::Start();

	m_MoveCompPtr = GetOwner()->GetComponent<MovementComponent>();
}

void BounceComponent::FixedUpdate()
{
	IComponent::FixedUpdate();
	if (m_Timer < BOUNCE_IMMUNITY)
		m_Timer += Time().fixedDeltaTime;
}

void BounceComponent::OnNotify(ISubject* subjectPtr, IEvent* event)
{
	IObserver::OnNotify(subjectPtr, event);

	if (BlockEvent* blockEvent = dynamic_cast<BlockEvent*>(event))
	{
		Bounce(blockEvent);
		if (m_NrBounces >= m_MaxNrBounces)
			GetOwner()->Destroy();
	}
}

void BounceComponent::Bounce(BlockEvent* event)
{
	if (m_Timer < BOUNCE_IMMUNITY)
		return;

	++m_NrBounces;
	m_Timer = 0;
	m_MoveCompPtr->SetDirection(glm::reflect(event->info.velocity, event->info.impactNormal));

}
