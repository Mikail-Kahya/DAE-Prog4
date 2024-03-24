#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

namespace mk
{
	class BoxColliderComponent : public Component
	{
	public:
		BoxColliderComponent() = default;
		~BoxColliderComponent() override = default;

		BoxColliderComponent(const BoxColliderComponent& other)					= delete;
		BoxColliderComponent(BoxColliderComponent&& other) noexcept				= delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other)		= delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) noexcept	= delete;

		bool IsOverlapping(BoxColliderComponent* other) const;
		const glm::vec3& GetBoxExtent() const;

	private:
		glm::vec3 m_Extent{};
	};
}
