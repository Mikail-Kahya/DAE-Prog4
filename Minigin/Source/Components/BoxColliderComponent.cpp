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

void BoxColliderComponent::CheckCollision(BoxColliderComponent* other)
{
	if (CanOverlap() && IsOverlapping(other))
	{
		Event event{ EventType::OBJECT_OVERLAP };
		event.SetData("other", other);
		Notify(event);

		event.SetData("other", this);
		other->Notify(event);
	}
}

CollisionType BoxColliderComponent::GetCollision() const
{
	return m_CollisionType;
}

void BoxColliderComponent::SetCollision(CollisionType type)
{
	m_CollisionType = type;
}

bool BoxColliderComponent::IsOverlapping(BoxColliderComponent* other) const
{
	const auto minMax{Geometry::GetBoxMinMax(other->GetOwner().GetWorldPosition(), other->GetBoxExtent()) };
	if (Geometry::PointInBox(minMax.first, GetOwner().GetWorldPosition(), GetBoxExtent()))
		return true;
	
	return Geometry::PointInBox(minMax.second, GetOwner().GetWorldPosition(), GetBoxExtent());
}

const glm::vec3& BoxColliderComponent::GetBoxExtent() const
{
	return m_Extent;
}

void BoxColliderComponent::SetExtent(const glm::vec3& extent)
{
	m_Extent = extent;
}

bool BoxColliderComponent::CanOverlap() const
{
	return m_CollisionType == CollisionType::overlapAll || m_CollisionType == CollisionType::overlapDynamic;
}
