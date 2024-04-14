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
	if (CanOverlap() && !m_IgnoreColliders.contains(otherPtr) && IsOverlapping(otherPtr))
	{
		Event event{ EventType::OBJECT_OVERLAP };
		event.SetData("other", otherPtr);
		Notify(event);

		event.SetData("other", this);
		otherPtr->Notify(event);
	}
}

void BoxColliderComponent::Ignore(BoxColliderComponent* colliderPtr) noexcept
{
	m_IgnoreColliders.insert(colliderPtr);
}

void BoxColliderComponent::StopIgnoring(BoxColliderComponent* colliderPtr) noexcept
{
	if (m_IgnoreColliders.contains(colliderPtr))
		m_IgnoreColliders.erase(colliderPtr);
}

CollisionType BoxColliderComponent::GetCollision() const noexcept
{
	return m_CollisionType;
}

const glm::vec3& BoxColliderComponent::GetBoxExtent() const noexcept
{
	return m_Extent;
}

bool BoxColliderComponent::IsOverlapping(BoxColliderComponent* other) const
{
	const auto minMax{Geometry::GetBoxMinMax(other->GetOwner().GetWorldPosition(), other->GetBoxExtent()) };
	if (Geometry::PointInBox(minMax.first, GetOwner().GetWorldPosition(), GetBoxExtent()))
		return true;
	
	return Geometry::PointInBox(minMax.second, GetOwner().GetWorldPosition(), GetBoxExtent());
}

void BoxColliderComponent::SetCollision(CollisionType type) noexcept
{
	constexpr int lastIdx{ static_cast<int>(CollisionType::none) };
	const int idx{ static_cast<int>(type) };

	m_CollisionType = (idx < 0 || idx > lastIdx) ? CollisionType::none : type;
}

void BoxColliderComponent::SetExtent(const glm::vec3& extent) noexcept
{
	m_Extent = extent;
}

bool BoxColliderComponent::CanOverlap() const
{
	return m_CollisionType == CollisionType::overlapAll || m_CollisionType == CollisionType::overlapDynamic;
}
