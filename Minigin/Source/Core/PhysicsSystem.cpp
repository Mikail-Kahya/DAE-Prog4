#include "PhysicsSystem.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "Geometry.h"

using namespace mk;

void PhysicsSystem::Update()
{
	// Very poor performance, fix later
	for (size_t idxFirst{}; idxFirst < m_BoxColliders.size() - 1; ++idxFirst)
	{
		for (size_t idxLast{idxFirst + 1}; idxLast < m_BoxColliders.size(); ++idxLast)
		{
			if (m_BoxColliders[idxFirst]->IsIgnoring(m_BoxColliders[idxLast]->GetOwner()) ||
				m_BoxColliders[idxLast]->IsIgnoring(m_BoxColliders[idxFirst]->GetOwner()) ||
				!IsOverlapping(m_BoxColliders[idxFirst], m_BoxColliders[idxLast]))
				continue;

			m_BoxColliders[idxFirst]->Collide(m_BoxColliders[idxLast]);
			m_BoxColliders[idxLast]->Collide(m_BoxColliders[idxFirst]);
		}
	}
}

void PhysicsSystem::RegisterCollider(BoxColliderComponent* colliderPtr)
{
	const auto foundIter = std::find(m_BoxColliders.begin(), m_BoxColliders.end(), colliderPtr);
	if (foundIter == m_BoxColliders.end())
		m_BoxColliders.push_back(colliderPtr);
}

void PhysicsSystem::UnRegisterCollider(BoxColliderComponent* colliderPtr)
{
	const auto foundIter = std::find(m_BoxColliders.begin(), m_BoxColliders.end(), colliderPtr);
	if (foundIter != m_BoxColliders.end())
		m_BoxColliders.erase(foundIter);
}

bool PhysicsSystem::IsOverlapping(BoxColliderComponent* a, BoxColliderComponent* b) const
{
	const auto minMax{ Geometry::GetBoxMinMax(b->GetOwner()->GetWorldPosition(), b->GetBoxExtent()) };
	if (Geometry::PointInBox(minMax.first, a->GetOwner()->GetWorldPosition(), a->GetBoxExtent()))
		return true;

	return Geometry::PointInBox(minMax.second, a->GetOwner()->GetWorldPosition(), a->GetBoxExtent());
}
