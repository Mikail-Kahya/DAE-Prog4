#include "BoxColliderComponent.h"

#include "GameObject.h"
#include "Geometry.h"

using namespace mk;

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
