#pragma once
#include "Component.h"
#include "glm/vec2.hpp"

namespace mk
{
	class MovementComponent final : public Component
	{
	public:
		MovementComponent(float maxLinearSpeed = 50.f, float maxAngularSpeed = 5.f, float acceleration = 1.f, float deceleration = 1.f);
		~MovementComponent() override = default;

		MovementComponent(const MovementComponent& other)				= delete;
		MovementComponent(MovementComponent&& other)					= delete;
		MovementComponent& operator=(const MovementComponent& other)	= delete;
		MovementComponent& operator=(MovementComponent&& other)			= delete;

		void FixedUpdate() override;

		// Normalizes in this function
		void SetDirection(const glm::vec2& direction);

		const glm::vec2& GetDirection() const;
		float GetSpeed() const;
		float GetSpeedSqr() const;

	private:
		void Accelerate(float acceleration);
		void Decelerate(float deceleration);

		bool IsMoving() const;
		bool ShouldMove() const;

		float m_MaxLinearSpeed{};
		float m_MaxAngularSpeed{};
		float m_AngularVelocity{};
		float m_Acceleration{};
		float m_Deceleration{};
		glm::vec2 m_Velocity{};
		glm::vec2 m_DesiredDirection{};
	};
}
