#include "PhysicsSystem.h"

#include "BoxColliderComponent.h"

using namespace mk;

void PhysicsSystem::Update()
{
	// Very poor performance, fix later
	for (auto a : m_BoxColliders)
	{
		for (auto b : m_BoxColliders)
		{
			if (a != b)
				a->CheckCollision(b);
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
