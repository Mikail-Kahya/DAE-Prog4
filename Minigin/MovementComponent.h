#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

namespace mk
{
	class MovementComponent final : public Component
	{
	public:
		MovementComponent() = default;
		~MovementComponent() override = default;

		MovementComponent(const MovementComponent& other)				= delete;
		MovementComponent(MovementComponent&& other)					= delete;
		MovementComponent& operator=(const MovementComponent& other)	= delete;
		MovementComponent& operator=(MovementComponent&& other)			= delete;

		void FixedUpdate() override;

		void SetVelocity(const glm::vec3& velocity);

		float GetSpeed() const;
		float GetSpeedSqr() const;

	private:
		glm::vec3 m_Velocity{};
	};
}
