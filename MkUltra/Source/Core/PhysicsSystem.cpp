#include "PhysicsSystem.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "Geometry.h"
#include "glm/gtx/intersect.hpp"

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


			m_BoxColliders[idxFirst]->Collide(GetCollisionInfo(m_BoxColliders[idxFirst], m_BoxColliders[idxLast]));
			m_BoxColliders[idxLast]->Collide(GetCollisionInfo(m_BoxColliders[idxLast], m_BoxColliders[idxFirst]));
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

CollisionInfo PhysicsSystem::GetCollisionInfo(BoxColliderComponent* a, BoxColliderComponent* b) const
{
	CollisionInfo result{};
	result.distance = FLT_MAX;
	result.hitCompPtr = b;

	const glm::vec2& moveDir{ a->GetMoveDirection() };
	std::vector<glm::vec2> vertices{};
	GetVertices(b->GetOwner()->GetWorldPosition(), b->GetBoxExtent(), vertices);

	const glm::vec2 pos{ a->GetOwner()->GetWorldPosition() };
	constexpr int nrVertices{ 4 };
	for (int idx{}; idx < nrVertices; ++idx)
	{
		const glm::vec2& p1{ vertices[idx] };
		const glm::vec2& p2{ vertices[(idx + 1) % nrVertices] };
		const glm::vec2 edge{ p2 - p1 };
		const float cross{ edge.x * moveDir.y - moveDir.x * edge.y };
		if (abs(cross) < FLT_EPSILON)
			continue;

		const glm::vec2 posToEdge{ p1 - pos };
		const float distance{ (edge.x * posToEdge.y - posToEdge.x * edge.y) / cross };

		if (distance > result.distance)
			continue;

		result.distance = distance;
		result.intersectionPoint = pos + distance * moveDir;
		result.impactNormal = glm::cross(glm::vec3{ edge, 0 }, glm::vec3{ 0, 0, 1 });
	}

	return result;
}

void PhysicsSystem::GetVertices(const glm::vec2& position, const glm::vec2& boxExtent, std::vector<glm::vec2>& vertices) const
{
	constexpr int nrVertices{ 4 };
	vertices.clear();
	vertices.resize(nrVertices);
	vertices[0] = position + boxExtent;
	vertices[1] = position - glm::vec2{ boxExtent.x, -boxExtent.y };
	vertices[2] = position - boxExtent;
	vertices[3] = position - glm::vec2{ -boxExtent.x, boxExtent.y };
}
