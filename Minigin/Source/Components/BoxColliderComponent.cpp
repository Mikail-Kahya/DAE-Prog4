#include "BoxColliderComponent.h"

#include "GameObject.h"
#include "Geometry.h"
#include "PhysicsSystem.h"

using namespace mk;

BoxColliderComponent::BoxColliderComponent()
{
	PhysicsSystem::GetInstance().RegisterCollider(this);
}

BoxColliderComponent::~BoxColliderComponent()
{
	PhysicsSystem::GetInstance().UnRegisterCollider(this);
}

void BoxColliderComponent::CheckCollision(BoxColliderComponent* otherPtr)
{
	if (m_IgnoreObjects.contains(otherPtr->GetOwner()))
		return;
	CollisionType type = otherPtr->GetOwner()->IsStatic() ? m_CollisionSettings.collisionStatic : m_CollisionSettings.collisionDynamic;
	switch (type)
	{
	case CollisionType::block:
		HandleBlock(otherPtr);
		break;
	case CollisionType::overlap:
		HandleOverlap(otherPtr);
		break;
	}
}

void BoxColliderComponent::Ignore(GameObject* colliderPtr) noexcept
{
	m_IgnoreObjects.insert(colliderPtr);
}

void BoxColliderComponent::StopIgnoring(GameObject* colliderPtr) noexcept
{
	if (m_IgnoreObjects.contains(colliderPtr))
		m_IgnoreObjects.erase(colliderPtr);
}

CollisionSettings BoxColliderComponent::GetCollision() const noexcept
{
	return m_CollisionSettings;
}

const glm::vec3& BoxColliderComponent::GetBoxExtent() const noexcept
{
	return m_Extent;
}

bool BoxColliderComponent::IsOverlapping(BoxColliderComponent* other) const
{
	const auto minMax{Geometry::GetBoxMinMax(other->GetOwner()->GetWorldPosition(), other->GetBoxExtent()) };
	if (Geometry::PointInBox(minMax.first, GetOwner()->GetWorldPosition(), GetBoxExtent()))
		return true;
	
	return Geometry::PointInBox(minMax.second, GetOwner()->GetWorldPosition(), GetBoxExtent());
}

void BoxColliderComponent::SetCollision(CollisionSettings settings) noexcept
{
	auto clampCollision = [](CollisionType type) -> CollisionType
		{
			constexpr int lastIdx{ static_cast<int>(CollisionType::ignore) };
			int idx{ static_cast<int>(type) };
			if (idx < 0 || idx > lastIdx)
				idx = lastIdx;
			return static_cast<CollisionType>(idx);
		};

	settings.collisionDynamic = clampCollision(settings.collisionDynamic);
	settings.collisionStatic = clampCollision(settings.collisionStatic);
	m_CollisionSettings = settings;
}

void BoxColliderComponent::SetExtent(const glm::vec3& extent) noexcept
{
	m_Extent = extent;
}

void BoxColliderComponent::HandleOverlap(BoxColliderComponent* otherPtr)
{
	if (!IsOverlapping(otherPtr))
		return;

	Event event{ EventType::OBJECT_OVERLAP };
	event.SetData("other", otherPtr);
	Notify(event);
	event.SetData("other", this);
	otherPtr->Notify(event);
}

void BoxColliderComponent::HandleBlock(BoxColliderComponent* otherPtr)
{
	if (!IsOverlapping(otherPtr))
		return;
}