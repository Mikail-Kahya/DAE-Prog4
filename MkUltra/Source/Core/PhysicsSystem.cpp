#include "PhysicsSystem.h"

#include <algorithm>

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "Geometry.h"
#include "Renderer.h"
#include "glm/gtx/intersect.hpp"

using namespace mk;

#ifdef NDEBUG
void PhysicsSystem::DrawDebug() const
{
	for (const Collider& collider : m_PhysicsBuffer)
	{
		const PhysicsInfo& info{ collider.second };
		const int halfWidth{ static_cast<int>(info.boxExtent.x) };
		const int halfHeight{ static_cast<int>(info.boxExtent.y) };
		Renderer::GetInstance().RenderRect(
			static_cast<int>(info.position.x) - halfWidth,
			static_cast<int>(info.position.y) - halfHeight,
			halfWidth * 2,
			halfHeight * 2,
			Color{ 155, 155, 0, 1 }
		);
	}
}
#endif

void PhysicsSystem::Update()
{
	HandleCollision();
	UpdateInformation();
}

void PhysicsSystem::RegisterCollider(BoxColliderComponent* colliderPtr)
{
	// Avoid duplicates
	const auto foundIter = std::find_if(m_PhysicsBuffer.begin(), m_PhysicsBuffer.end(), [colliderPtr](const Collider& collider)
		{
			return colliderPtr == collider.first;
		});

	if (foundIter != m_PhysicsBuffer.end())
		return;

	m_PhysicsBuffer.emplace_back(Collider{ colliderPtr, GetPhysicsInfo(colliderPtr) });
}

void PhysicsSystem::UnRegisterCollider(BoxColliderComponent* colliderPtr)
{
	const auto foundIter = std::find_if(m_PhysicsBuffer.begin(), m_PhysicsBuffer.end(), [colliderPtr](const Collider& collider)
		{
			return colliderPtr == collider.first;
		});
	if (foundIter != m_PhysicsBuffer.end())
		m_PhysicsBuffer.erase(foundIter);
}

void PhysicsSystem::HandleCollision() const
{
	const size_t nrColliders{ m_PhysicsBuffer.size() };
	// iterate over every one except the last
	// the last iteration was covered by every iteration before it
	for (size_t idxFirst{}; idxFirst < nrColliders - 1; ++idxFirst)
	{
		for (size_t idxSecond{ idxFirst + 1 }; idxSecond < nrColliders; ++idxSecond)
		{
			const Collider& firstCollider{ m_PhysicsBuffer[idxFirst] };
			const Collider& secondCollider{ m_PhysicsBuffer[idxSecond] };
			const bool isFirstIgnoring{ firstCollider.first->IsIgnoring(secondCollider.first->GetOwner()) };
			const bool isSecondIgnoring{ secondCollider.first->IsIgnoring(firstCollider.first->GetOwner()) };

			if (isFirstIgnoring && isSecondIgnoring)
				continue;

			if (!IsOverlapping(firstCollider.second, secondCollider.second))
				continue;

			if (!isFirstIgnoring)
			{
				CollisionInfo info{ GetCollisionInfo(firstCollider.second, secondCollider.second) };
				info.hitCompPtr = secondCollider.first;
				firstCollider.first->Collide(info);
			}

			//if (!isSecondIgnoring)
			//{
				//info = GetCollisionInfo(secondCollider.second, firstCollider.second);
				//info.hitCompPtr = firstCollider.first;
				//secondCollider.first->Collide(info);
			//}
		}
	}
}

void PhysicsSystem::UpdateInformation()
{
	for (Collider& collider : m_PhysicsBuffer)
		collider.second = GetPhysicsInfo(collider.first);
}

PhysicsInfo PhysicsSystem::GetPhysicsInfo(const BoxColliderComponent* colliderPtr)
{
	return {
		.position = colliderPtr->GetOwner()->GetWorldPosition(),
		.boxExtent = colliderPtr->GetBoxExtent()
	};
}

bool PhysicsSystem::IsOverlapping(const PhysicsInfo& a, const PhysicsInfo& b)
{
	const auto minMax{ Geometry::GetBoxMinMax(b.position, b.boxExtent) };
	if (Geometry::PointInBox(minMax.first, a.position, a.boxExtent))
		return true;

	return Geometry::PointInBox(minMax.second, a.position, a.boxExtent);
}

CollisionInfo PhysicsSystem::GetCollisionInfo(const PhysicsInfo& a, const PhysicsInfo& b)
{
	CollisionInfo result{};
	result.distance = FLT_MAX;

	const glm::vec2 ray{ b.position - a.position };

	std::vector<glm::vec2> vertices{};
	GetVertices(b.position, b.boxExtent, vertices);

	const glm::vec2 pos{ a.position };
	constexpr int nrVertices{ 4 };
	for (int idx{}; idx < nrVertices; ++idx)
	{
		const glm::vec2& p1{ vertices[idx] };
		const glm::vec2& p2{ vertices[(idx + 1) % nrVertices] };
		const glm::vec2 edge{ p2 - p1 };
		const float cross{ edge.x * ray.y - ray.x * edge.y };
		if (abs(cross) < FLT_EPSILON)
			continue;

		const glm::vec2 posToEdge{ p1 - pos };
		const float distance{ (edge.x * posToEdge.y - posToEdge.x * edge.y) / cross };

		if (distance > result.distance)
			continue;

		result.distance = distance;
		result.intersectionPoint = pos + distance * glm::normalize(ray);
		result.impactNormal = glm::normalize(glm::cross(glm::vec3{ edge, 0 }, glm::vec3{ 0, 0, 1 }));
	}

	return result;
}

void PhysicsSystem::GetVertices(const glm::vec2& position, const glm::vec2& boxExtent, std::vector<glm::vec2>& vertices)
{
	constexpr int nrVertices{ 4 };
	vertices.clear();
	vertices.resize(nrVertices);
	vertices[0] = position + boxExtent;
	vertices[1] = position - glm::vec2{ boxExtent.x, -boxExtent.y };
	vertices[2] = position - boxExtent;
	vertices[3] = position - glm::vec2{ -boxExtent.x, boxExtent.y };
}