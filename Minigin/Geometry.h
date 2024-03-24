#pragma once
#include <utility>

#include "glm/vec3.hpp"

namespace Geometry
{
	bool PointInBox(const glm::vec3& point, const glm::vec3& location, const glm::vec3& boxExtent);
	std::pair<glm::vec3, glm::vec3> GetBoxMinMax(const glm::vec3& location, const glm::vec3& boxExtent);
}
