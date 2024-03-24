#include "Geometry.h"

using namespace Geometry;

bool Geometry::PointInBox(const glm::vec3& point, const glm::vec3& location, const glm::vec3& boxExtent)
{
	const glm::vec3 min{ location - boxExtent };
	const glm::vec3 max{ location + boxExtent };

	if (min.x > point.x || point.x > max.x)
		return false;

	if (min.y > point.y || point.y > max.y)
		return false;

	return min.z < point.z && point.z < max.z;
}

std::pair<glm::vec3, glm::vec3> Geometry::GetBoxMinMax(const glm::vec3& location, const glm::vec3& boxExtent)
{
	return { location - boxExtent, location + boxExtent };
}