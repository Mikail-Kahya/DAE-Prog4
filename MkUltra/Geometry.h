#pragma once
#include <utility>

#include "glm/vec2.hpp"

namespace Geometry
{
	bool PointInBox(const glm::vec2& point, const glm::vec2& location, const glm::vec2& boxExtent);
	std::pair<glm::vec2, glm::vec2> GetBoxMinMax(const glm::vec2& location, const glm::vec2& boxExtent);
}
