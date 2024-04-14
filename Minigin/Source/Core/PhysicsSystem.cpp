#include "PhysicsSystem.h"

#include "BoxColliderComponent.h"

using namespace mk;

void PhysicsSystem::Update()
{
	// Very poor performance, fix later
	for (size_t idxFirst{}; idxFirst < m_BoxColliders.size() - 1; ++idxFirst)
	{
		for (size_t idxLast{idxFirst + 1}; idxLast < m_BoxColliders.size(); ++idxLast)
			m_BoxColliders[idxFirst]->CheckCollision(m_BoxColliders[idxLast]);
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
